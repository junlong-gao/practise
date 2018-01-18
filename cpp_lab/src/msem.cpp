#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
#include <cstring>
#include <exception>
#include <unordered_map>
#include "msem.h"

namespace msem {

    using namespace std;

    class Foo {
        char *cstring; // raw pointer used as a handle to a dynamically-allocated memory block
    public:
        Foo(const char *arg)
                : cstring(new char[std::strlen(arg) + 1]) {// allocate
            cout << "default constructor is called" << endl;
            std::strcpy(cstring, arg); // populate
        }

        ~Foo() {
            cout << "destructor is called" << endl;
            if (cstring == nullptr) cout << "this has been moved, relax." << endl;
            delete[] cstring;  // deallocate
        }

        void mutate_dump() {
            if (cstring) {
                cout << cstring << endl;
            } else {
                cout << "the object is moved" << endl;
                cout << "no resource is here" << endl;
            }
        }

        void dump() const {
            if (cstring) {
                cout << cstring << endl;
            } else {
                cout << "the object is moved" << endl;
                cout << "no resource is here" << endl;
            }
        }

        /*
         * in general, a rvalue passed in
         * implies the underlying object can be
         * moved instead of making a copy
         * for example, if a value is return
         * from a factory
         * the two overloading is necessary
         * machinism to distinguish the difference
         * and call the correct constructor
         */

        Foo(const Foo &other) {// copy constructor
            cout << "copy constructor called" << endl;
            cstring = new char[std::strlen(other.cstring) + 1];
            std::strcpy(cstring, other.cstring);
        }

        Foo(Foo &&other) : cstring(other.cstring) { // move constructor c++11
            cout << "move constructor called" << endl;
            other.cstring = nullptr;
        }

        Foo &operator=(const Foo &other) {// copy assignment
            cout << "copy assignment called" << endl;
            delete[] cstring;
            cstring = new char[std::strlen(other.cstring) + 1];
            std::strcpy(cstring, other.cstring);
            return *this;
        }

        Foo &operator=(Foo &&other) { // move assignment  c++11
            cout << "move assignment called" << endl;
            delete[] cstring;
            cstring = other.cstring;
            other.cstring = nullptr;
            return *this;
        }
    };

    /*
     * a toy implementation of move:
     * cast the argument variable into
     * a variable of right reference
     */
    template<typename T>
    typename remove_reference<T>::type &&
    MyMove(T &&param) {
        using ReturnType = typename
        remove_reference<T>::type &&;
        return static_cast<ReturnType>(param);
    }

    string foo() {
        return "i am from foo";
    }

    Foo give_foo() {
        return Foo("I am an unnamed returned foo");
    }

    Foo give_named_foo() {
        Foo f("I am a returned named foo");
        return f;
    }

    void take_foo_value(Foo foo) {
        cout << "pass by value" << endl;
        foo.dump();
    }

    void take_foo_value_mutate(Foo foo) {
        cout << "pass by mutatable value" << endl;
        foo.mutate_dump();
    }

    void take_foo_lvalueref(Foo &foo) {
        cout << "pass by lvalue ref" << endl;
        foo.dump();
    }

    void take_foo_const_lvalueref(const Foo &foo) {
        cout << "pass by const lvalue ref" << endl;
        foo.dump();
    }

    void take_foo_rvalueref(Foo &&foo) {
        cout << "pass by rvalue ref" << endl;
        foo.dump();
    }

    class Bar {
        Foo foo;
    public:
        Bar(Foo &&foo_) : foo(std::move(foo_)) {
            cout << "  Bar constructor:rvalue ref + move" << endl;
        }

        Bar(Foo &foo_) : foo(foo_) {
            cout << " Bar constructor:lvalue ref" << endl;
        }

        Bar(const Foo &foo_) : foo(foo_) {
            cout << " Bar constructor:const lvalue ref" << endl;
        }
    };

    class Baz {
        vector<Foo> foos;
    public:
        /*
        Baz(vector<Foo>&& foos_):foos(foos_){ //wrong
            cout << "move the object into foos" << endl;
        }
         */
        Baz(vector<Foo> &&foos_) : foos(std::move(foos_)) {
            cout << "move the object into foos" << endl;
            cout << "the vector is moved" << endl;
            cout << "moving a vector is just adjusting pointer" << endl;
        }

        Baz(vector<Foo> &foos_) : foos(foos_) {
            cout << "copy the object into foos" << endl;
            cout << "the vector is copied" << endl;
            cout << "all copy constructor is called" << endl;
        }

    };

    class FooFactory {
    public:
        template<typename ...Ts>
        static unique_ptr<Foo>
        give_foo(string platform, Ts &&...param) {
            cout << "building foo in " << platform << endl;

            return unique_ptr<Foo>(new Foo(std::forward<Ts>(param)...));
        }
    };

    class BarFactory {
    public:
        template<typename ...Ts>
        static unique_ptr<Bar>
        give_bar(string platform, Ts &&...param) {
            cout << "building bar in " << platform << endl;

            return unique_ptr<Bar>(new Bar(std::forward<Ts>(param)...));
        }
    };


    void demo() {

        /*
         * Copy elison
         */
        vector<Foo> better_foos; //
        better_foos.reserve(10000);
        cout << "pass into a value para by a rvalue" << endl;
        cout << endl<<"---> from unamed rvalue to plain:" << endl;
        take_foo_value(give_foo());
        cout << endl<<" no copy happens. This is copy elision" << endl;

        cout << endl<<"---> from named rvalue to plain:" << endl;
        take_foo_value(give_named_foo());
        cout << endl<<" no copy happens. This is copy elision" << endl;

        cout << endl<<"---> from constructor:" << endl;
        Foo foo3(Foo("foo3"));
        cout << endl<<" no copy happens. This is copy elision" << endl;

        cout << endl<<"---> from constructor and implict type conversion:" << endl;
        Foo foo1 = "foo1";
        cout << endl<<  "no copy happens. This is copy elision" << endl;

        cout << endl << "---> inilize list, still copying" << endl;
        vector<Foo> foos{"foo4"};
        cout << endl<< "--- copy happens. No copy elision" << endl;

        cout << endl << endl << "---move sementics---" << endl;
        /****/
        cout << endl << "---> emplace back with default constructor" << endl;
        better_foos.emplace_back("foo5");
        cout << endl<< "--- no copy no move happens. perfect forwarding" << endl<<endl;

        cout << endl << "---> push back with default constructor" << endl;
        better_foos.push_back("foo5");
        cout << endl<< " 0 copy 1 moved" << endl<<endl;
        /****/

        /****/
        cout << endl << "---> emplace back with constructed obj" << endl;
        better_foos.emplace_back(Foo("foo6"));
        cout << endl << " 1 move" << endl << endl;

        cout << endl << "---> push back with constructed obj" << endl;
        better_foos.push_back(Foo("foo6"));
        cout << endl << " 1 move" << endl << endl;

        cout << endl << "---> push back with obj but use move" << endl;
        /*
         * warning: moving a temporary object prevents copy elision [-Wpessimizing-move]
         */
        better_foos.push_back(move(Foo("foo10")));
        cout << endl << " 1 move!" << endl;
        /****/

        /****/
        cout << endl << "---> emplace back with lvalue" << endl;
        better_foos.emplace_back(foo1);
        cout << endl << " 1 copy" << endl << endl;

        cout << endl << "---> push back with lvalue " << endl;
        better_foos.push_back(foo1);
        cout << endl << " 1 copy" << endl << endl;

        cout << endl << "---> push back with lvalue but use move" << endl;
        better_foos.push_back(move(foo1));
        cout << endl << " 1 move" << endl;
        /****/

        /****/
        cout << endl << "---> emplace back return named" << endl;
        better_foos.emplace_back(give_named_foo());
        cout << endl << " 1 move" << endl;

        cout << endl << "---> push back return named" << endl;
        better_foos.push_back(give_named_foo());
        cout << endl << " 1 move" << endl;

        /****/


        cout << endl << "--- parameter passing" << endl;

        //Foo &ret_l = give_named_foo(); won't compile
        /*
         * this is useless too:
        cout << "assign a rvalue reference to a return value" << endl;
        Foo &&ret_r = give_named_foo(); //ret_r is a left value

        cout << "---- pass rvalue ref into rvalue ref" << endl;
        take_foo_rvalueref(ret_r); //and cannot bind to right ref
        cout << "----" << endl;
         */

        Foo foo2(std::move(foo1));
        foo1.dump();
        foo2.dump();

        Foo foo4("foo4");

        cout << "---> construction" << endl;
        Bar bar1(foo4);
        const Foo &foo6 = foo4;
        Bar bar2(foo6);
        cout << " (const) named value (lvalue) is copyed" << endl;
        Bar bar3(std::move(foo4));
        cout << " pure move semantics" << endl;
        Bar bar4(give_foo());
        cout << " a tmp is created and move semantics, not copy elison" << endl;
        /* same as above
        Bar bar5(std::move(give_foo()));
        cout << " a tmp is created and move semantics, not copy elison" << endl;
         */

        cout << "---> construct vector of foos:" << endl;
        //vector<Foo> baz_foos{Foo("foo10"), Foo("foo11")}; //bad, don't do it

        vector <Foo> baz_foos1;
        baz_foos1.reserve(2);
        baz_foos1.emplace_back("foo10");
        baz_foos1.emplace_back("foo11");

        vector <Foo> baz_foos2;
        baz_foos2.reserve(2);
        baz_foos2.emplace_back("foo10");
        baz_foos2.emplace_back("foo11");

        cout << "--->constructing baz1 using move" << endl;
        Baz baz1(std::move(baz_foos1));
        cout << "--->constructing baz2 using copy" << endl;
        Baz baz2(baz_foos2);

        cout << "--->Foo factory:" << endl;
        auto built_foo = FooFactory::give_foo("windows", "foo factory pattern");
        //unique_ptr<Foo> bad = built_foo; forbidden
        cout << "the parameters are perfectly forwarded into foo default constructor" << endl;

        cout << "--->Bar factory:" << endl;
        Foo foobar("bar factory pattern");
        auto built_bar = BarFactory::give_bar("windows", std::move(foobar));
        //unique_ptr<Foo> bad = built_foo; forbidden
        cout << "the parameters are perfectly forwarded into bar move constructor" << endl;
        cout << endl << endl << "---move sementics---" << endl;
    }
}
