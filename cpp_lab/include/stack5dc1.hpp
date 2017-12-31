#include <iostream>
#include <vector>
#include <deque>

namespace stack5dc1 {
    template <typename T>
    class Stack{
    private:
        std::deque<T> elems;
        int numElems;
    public:
        Stack();
        void push(T const&);
        T pop();
        T top() const;
        bool empty() const {
            return elems.empty();
        }
        template <typename T2>
        Stack<T>& operator=(Stack<T2> const&);
        void dump(){
          for(auto it = elems.begin(); it!=elems.end(); ++it){
            std::cout << *it << std::endl;
          }
        }
    };

    template <typename T>
    Stack<T>::Stack(): numElems(0){;};

    template <typename T>
    void Stack<T>::push(T const& elem){
        this->elems.push_back(elem);
        this->numElems++;
    };

    template <typename T>
    T Stack<T>::pop(){
        if(this->empty()){
            throw std::out_of_range("Stack<>::pop(): stack is empty");
        }
        T ret = this->elems.back();
        this->elems.pop_back();
        this->numElems--;
        return ret;
    }

    template <typename T>
    T Stack<T>::top() const{
        if(this->empty()){
            throw std::out_of_range("Stack<>::pop(): stack is empty");
        }
        return this->elems.back();
    }

    template<typename T>
    template<typename T2>
    Stack<T>& Stack<T>::operator=(Stack<T2> const& rhs){
        if((void*)this == (void*)&rhs){
            return *this;
        }
        this->elems.clear();
        /* you can't do this (why?)
         as different types cannot access private members, since
         Stack<T> and Stack<T2> are considered as different types.
        for(auto it = rhs.elems.begin(); it!=rhs.elems.end(); ++it){
            this->elems.push_back(*it);
        }
         */
        // ctor?
        Stack<T2> tmp(rhs);
        while(!tmp.empty()){
          elems.push_back(tmp.top());
          tmp.pop();
        }
        return *this;
    }

    void demo(){
        std::cout << "starting demo stack5dc1" << std::endl;
        stack5dc1::Stack<int> s2;
        s2.push(10);
        s2.dump();
        //s2.pop();
        stack5dc1::Stack<double> s3;
        s3= s2;
        s3.dump();
        std::cout << "ending demo stack5dc1" << std::endl;
    }
}
