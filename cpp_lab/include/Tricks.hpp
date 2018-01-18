#ifndef TRICKS_H_
#define TRICKS_H_
#include <iostream>
namespace Tricks{
   /*
    * "How do you pronounce SFINE? S-FINE or sfine? I prefer the first as
    * it sounds like latin, makes you look more educated. Unlike the latter,
    * sounds like you are spitting or something."
    */
/*
2.1
Compile time assertions
Now is available as static assert after c++11
*/
    template <class T>
    struct data_structure
    {
        static_assert(std::is_default_constructible<T>::value,
                      "Data Structure requires default-constructible elements");
    };
    struct no_default
    {
        no_default () = delete;
    };
    void demo_2_1(){
        data_structure<int> ds_ok;
        //data_structure<no_default> ds_error;
    }
/*
2.2 partial specialization of classes:
*/
    template <typename U, typename V>
    struct Widget{
        Widget(){
            std::cout << "generic" << std::endl;
        }
    };

    template<>
    struct Widget<int, double>{
        Widget(){
            std::cout << "specialized as int, double" << std::endl;
        }
    };

    template<typename V>
    struct Widget<int, V>{
        Widget(){
            std::cout << "specialized as int, partial specialized at " << V::value << std::endl;
        }
    };
    template <int v>
    struct dummy{
        // enum is a special type where each enumerator is a value
        //each enumerator can be accessed as dummy::value
        enum {value = v};
    };

    void demo_2_2(){
        Widget<int, dummy<-1>> w;
    }

/*
2.3
Compile time int to type mapping
*/
    template <int v>
    struct Int2Type{
        // enum is a special type where each enumerator is a value
        //each enumerator can be accessed as dummy::value
        enum {value = v};
    };
/*
example: lets say we have a container type
*/
    template <typename T, bool isPolymorphic>
    class NiftyContainer{
/*
and you want to do something involving copying T.
But copying T relies on the compile time constant
isPolymorphic
*/
        /*
    public:
        void DoSomething(T* pSomeObj){
            if(isPolymorphic){
                // poly clone
                T* pNewObj = pSomeObj->Clone();
            }else{
                // non poly copy
                T* pNewObj = new T(*pSomeObj);
            }
        }
        */
/*
Unfortunately this class is useless, as this depends on
both clone and copy constructions available for T.
If T is an int, this will never compile.
The correct way is to leverage compile time typeselection
and function overloading
*/
        void DoSomething(T* pObj, Int2Type<true>){
            T* pNewObj = pObj->Clone();
        }
        void DoSomething(T* pObj, Int2Type<false>){
            T* pNewObj = new T(*pObj);
            //do something
            std::cout << *pNewObj << std::endl;
            delete pNewObj;
        }
    public:
        void DoSomething(T* pObj){
            DoSomething(pObj, Int2Type<isPolymorphic>());
        }
    };
    void demo_2_3(){
        NiftyContainer<int, false> test;
        int a = 2;
        test.DoSomething(&a);
    }

    namespace s5{
    /*
    2.4
    Compile time type to type mapping
    */
    template <typename T>
    struct Type2Type
    {
       using OriginalType = T;
    };
    /*
    Let's say you have a template function that takes 2 types

    template <class T, class U>
    T* Create(const U& arg){
        return new T(arg);
    }

    Yet you want to use it for T=widget, which requires 2 args,
    the second one being fix -1 for some legacy code reasons.
    */
    struct Widget{
        Widget(int a, int b){
            std::cout << a << " and " << b << std::endl;
        }
    };
    /*
    the following partial specialization is not going to work as you cannot
    partially specialize functions:
    template <class U>
    Widget* Create<Widget, U>(const U& arg){
        return new Widget(arg, -1);
    }
    so what's left for you is the function overloading to add a dummy second para:
    template <class T, class U>
    T* Create(const U& arg, T){
        return new T(arg);
    }
    then
    template <class U>
    Widget* Create(const U& arg, Widget // costy dummy ) {
       return new Widget(arg, -1);
    }
    The obvious down side is that everytime you use Create, a costy dummy obj
    is constructed via default constructor (and doesn't compile for those
    cannot be constructed using default ctor)
    */
    // so you need a light weight type selector from type:
    template <class T, class U>
    T* Create(const U& arg, Type2Type<T>){
        return new T(arg);
    }
    // "fake" partial specialization for widget:
    template <class U>
    Widget* Create(const U& arg, Type2Type<Widget>){
        return new Widget(arg, -1);
    }

    void demo(){
        std::string* pstr = Create("Hello", Type2Type<std::string>());
        Widget* pW = Create(2, Type2Type<Widget>());
    }
    }
    /*
    type selection
    the following type selection suggested in mcppd 2.6 selects T
    if flag is true, U otherwise
    */
    template <bool flag, typename T, typename U>
    struct Select{
        using Result = T;
    };
    // specialization of a false
    template<typename T, typename U>
    struct Select<false, T, U>{
        using Result = U;
    };

    namespace s6{
        template <int v>
        struct dummy{
            enum {value = v};
        };

        void demo(){
            static_assert(Select<true, dummy<0>, dummy<1>>::Result::value == 0, "compile time type selection");
            //static_assert(Select<false, dummy<0>, dummy<1>>::Result::value == 0, "compile time type selection failed");

        }
    }
    namespace s7{
        /*
        compile time convertibility check
        implemented in c++11 Type traits
        "Traits are a generic programming technique that allows compile-time decisions to be made based on types,
        much as you would make runtime decisions based on values"
        */
    }
}

namespace YouShouldNotBeHere {
   namespace EnableIf {
      template<bool B, class T= void>
      struct enable_if {};

      template<class T>
      struct enable_if<true, T> { using type = T; };

      template<bool B, class T = void>
      using enable_if_t = typename enable_if<B, T>::type;

      template <typename T>
      struct is_int { enum { value = false }; };

      template <>
      struct is_int<int> { enum { value = true }; };

      template <typename W, typename T = enable_if_t<is_int<W>::value, W>>
      void say() {
         std::cout << "hello" << std::endl;
      }

      void demo() {
         say<int>();
         say<float>(); // this will not compile as the enable_if selection
         //failure
         //Tricks.hpp:240:12: note: candidate template ignored: requirement 'is_int<float>::value' was not satisfied [with W = float]
         //      void say() {
      }
   }
}


#endif
