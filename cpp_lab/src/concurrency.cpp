//
// Created by Junlong Gao on 11/27/16.
//

#include "concurrency.h"
#include <thread>
#include <algorithm>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <string>
#include <vector>
#include <deque>
#include <cassert>

namespace concurrency{
    using namespace std;
    class ThreadRAII{
        thread th;
    public:
        template <typename ...Ts>
        ThreadRAII(Ts&& ...params):th(forward<Ts>(params)...){;}

        ThreadRAII(ThreadRAII&& other) = default; //not so easy,
        // let compiler do the job here.

        ThreadRAII& operator=(ThreadRAII&& other) = default;
        ~ThreadRAII(){
            if(th.joinable()){
                th.join();
            }
        }
    };
    class Wiget{
        string value;
    public:
        Wiget(string&& data_= "default"):value(std::move(data_)){
            cout << "default constructor" << endl;
        }
        Wiget(string&& data_ , string&& data_2 ):value(string(data_)+string(data_2)){
            cout << "default constructor" << endl;
        }
        ~Wiget(){
            cout << value << " destoryed" << endl;
        }

        Wiget(Wiget&& other){
            cout << other.value << " moved ctor" <<endl;
            value = std::move(other.value);
        }
        Wiget(const Wiget& other){
            cout << other.value << " copied ctor" <<endl;
            value = other.value;
        }

        void operator=(Wiget&& other){
            cout << other.value << " assigned moved" <<endl;
            value = std::move(other.value);
        }

        void operator=(const Wiget& other){
            cout << other.value << " assigned copied" <<endl;
            value = other.value;
        }

        template <typename ...Ts>
        void set(Ts&& ...data){
            value = string(forward<Ts>(data)...);
        }
        void dump(){
            cout << value << endl;
        }
    };
    void demo(){
        auto pw = std::make_unique<Wiget>();
        auto pw2 = std::make_unique<Wiget>();
        pw->set("testing");
        cout << "---" << endl;
        pw->dump();
        cout << "---" << endl;
        pw->set(to_string(12));
        cout << "---" << endl;
        pw->dump();

        cout << "---" << endl;
        auto func = [pw = std::move(pw),
                     pw2 = std::move(pw2)]{ //init capture
            pw->set("lambda");
            pw2->set("another captured");
            pw->dump();
        };
        if(pw != nullptr || pw2 != nullptr){
            assert(0);
        }
        cout << "---" << endl;
        func();
        cout << "---" << endl;

        //generic lambdas
        auto f = [](auto x){
            x ->dump();
            return 0;
        };
        f(make_unique<Wiget>());
        cout << "---" << endl;
        auto g = [](auto&&... x){
            Wiget w(forward<decltype(x)>(x)...); //x's type will be the deduced type
            //if x is rvalue passed in, it will be a rvalue ref
            //if it is lvalue, it will be a lvalue ref
            w.dump();
            return 0;
        };
        auto h = [](auto&& x){
            Wiget w(x); //x is lvalue, impossible to perform rightvalueness
            //move ctor, a copy is called here.
            w.dump();
            return 0;
        };
        cout << "--- this will correctly deduced into"
                " string and perfectly forward into default constructor" << endl;
        g("test");
        cout << "---" << endl;
        Wiget to_move("to_move");
        cout << "--- this will correctly deduced into rvalue ref and"
                " perfectly forward to call move constructor:" << endl;
        g(std::move(to_move));
        cout << "---" << endl;
        Wiget to_copy("to_copy");
        h(std::move(to_copy));
        cout << "---" << endl;
    };
}

namespace concurrency{
    using lock_t = unique_lock<mutex>;
    struct RWlock::impl{
        int activeReaders, activeWriters, waitingReaders, waitingWriters;
        mutex lock;
        condition_variable readerCond, writeCond;
        bool readerShouldWait(){
            //in favor of writer
            if(activeWriters || waitingWriters) return true;
            return false;
        }
        bool writeShouldWait(){
            if(activeReaders || activeWriters) return true;
            return false;
        }
        impl(){
            activeReaders = activeWriters = 0;
            waitingReaders = waitingWriters = 0;
        }
    };

    RWlock::RWlock():rw_impl(new impl) {

    }
    RWlock::~RWlock(){
        delete rw_impl;
    }

    void RWlock::read_lock() {
        lock_t mtx(rw_impl->lock);
        rw_impl->waitingReaders++;
        while(rw_impl->readerShouldWait()){
            rw_impl->readerCond.wait(mtx);
        }
        rw_impl->activeReaders ++;
        rw_impl->waitingReaders --;
    }

    void RWlock::write_lock() {
        lock_t mtx(rw_impl->lock);
        rw_impl->waitingWriters++;
        while(rw_impl->writeShouldWait()){
            rw_impl->writeCond.wait(mtx);
        }
        rw_impl->activeWriters ++;
        rw_impl->waitingWriters --;
    }

    void RWlock::read_unlock() {
        lock_t mtx(rw_impl->lock);
        rw_impl->activeReaders--;
        if(rw_impl->activeReaders==0 && rw_impl->waitingWriters){
            //in favor of write
            rw_impl->writeCond.notify_one();
        }
    }

    void RWlock::write_unlock() {
        lock_t mtx(rw_impl->lock);
        rw_impl->activeWriters--;
        assert(rw_impl->activeWriters == 0);
        if(rw_impl->waitingWriters){
            //in favor of write
            rw_impl->writeCond.notify_one();
        }else if(rw_impl->waitingReaders){
            rw_impl->readerCond.notify_all();
        }
    }


    void test_rwlock(){
        RWlock rwlock;
        int data = 0;

        vector<ThreadRAII> workers;
        for(int i = 0; i < 10000; ++i){
            workers.emplace_back([&](){
                rwlock.read_lock();
                cout << data << endl;
                rwlock.read_unlock();
            });
            ThreadRAII([&](){
                rwlock.write_lock();
                data = i;
                rwlock.write_unlock();
            });
        }
    }


}

namespace concurrency{
    using lock_t = unique_lock<mutex>;
    template <typename T>
    struct BoundedBuffer<T>::impl{
        deque<T> data;
        mutex mtx;
        unsigned int size;
        condition_variable getter, putter;
        impl(unsigned int size_):size(size_){
            ;
        }
        bool getterShouldWait(){
            return data.empty();
        }
        bool putterShouldWait(){
            return data.size() == size;
        }
    };

    template <typename T>
    void BoundedBuffer<T>::put(T && obj) {
        lock_t mtx(bb_impl->mtx);

        while(bb_impl->putterShouldWait()){
            bb_impl->putter.wait(mtx);
        }
        bb_impl->data.emplace_back(std::move(obj));
        bb_impl->getter.notify_one();
    }

    template <typename T>
    T BoundedBuffer<T>::get(){
        lock_t mtx(bb_impl->mtx);

        while(bb_impl->getterShouldWait()){
            bb_impl->getter.wait(mtx);
        }
        T ret(std::move(bb_impl->data.front()));
        bb_impl->data.pop_front();
        bb_impl->putter.notify_one();
        return ret;
    }
    template <typename T>
    BoundedBuffer<T>::BoundedBuffer(unsigned size):bb_impl(new impl(size)){
        ;
    }
    template <typename T>
    BoundedBuffer<T>::~BoundedBuffer(){
        delete bb_impl;
    }
    void test_bb(){
        BoundedBuffer<int> bb(3);
        vector<int> output;
        mutex lock;
        condition_variable full;

        vector<ThreadRAII> workers;
        for(int i = 0; i < 100; ++i){
            workers.emplace_back([&](int i){
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1s);
                bb.put(int(i));
            }, i);
        }
        for(int i = 100; i < 200; ++i){
            workers.emplace_back([&](int i){
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(1s);
                bb.put(int(i));
            }, i);
        }
        for(int i = 0; i < 200; ++i){
            workers.emplace_back([&](){
                int out = bb.get();
                lock.lock();
                output.emplace_back(out);
                if(output.size() == 200) full.notify_one();
                lock.unlock();
            });
        }
        while(true) {
            unique_lock<mutex> mtx(lock);
            if(output.size() < 200){
                full.wait(mtx);
            }
            if(output.size() == 200) break;
        }
        for(auto& out:output){
            cout << out << endl;
        }
        cout << endl << output.size() << endl;
    }
}