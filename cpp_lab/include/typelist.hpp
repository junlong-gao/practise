#ifndef TYPELIST_H_
#define TYPELIST_H_
#include <type_traits>
#include "Tricks.hpp"
namespace TL{

    class NullType {};

    /*
    EmptyType is a legal type to inherit from,
     and you can pass around values of type EmptyType.
      You can use this insipid type as a default ("don't care") 
      type for a template. 
    */
    struct EmptyType {};

    template <class T, class U>
    struct Typelist{
        using Head = T;
        using Tail = U;
    };
    //quick starters:
    #define TYPELIST_1(T1) Typelist<T1, NullType>
    #define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) >
    #define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) > 
    #define TYPELIST_4(T1, T2, T3, T4) \
    Typelist<T1, TYPELIST_3(T2, T3, T4) >

    //length
    template<class TList> struct Length;
    //a total specialization
    template<> struct Length<NullType>{
        enum {value = 0};
    };
    //a partial specilization for 
    // all type Typelist<T, U>
    template< class T, class U>
    struct Length< Typelist<T, U>>{
        enum {value = 1 + Length<U>::value};
    };

    //index at
    template <class TList, unsigned int index> struct TypeAt;
    //non-null base case
    template<typename Head, typename Tail>
    struct TypeAt<Typelist<Head, Tail>, 0>{
        using Result = Head;
    };
    //recurse
    template<typename Head, typename Tail, unsigned int i>
    struct TypeAt<Typelist<Head, Tail>, i>{
        using Result = typename TypeAt<Tail, i-1>::Result;
    };

    //indexOf:
    template <class TList, class T> struct IndexOf;
    template<typename T>
    struct IndexOf<NullType, T>{
        enum {value=-1};
    };
    template<typename Tail,typename T>
    struct IndexOf<Typelist<T, Tail>, T>{
        enum {value= 0};
    };
    template<typename Head, typename Tail, class T>
    struct IndexOf<Typelist<Head, Tail>, T>{
        // you cannot do 
        // enum {value = IndexOf<Tail, T>::value + 1};
        // for if value is -1, then ...
    private:
        enum { t = IndexOf<Tail, T>::value};
    public:
        enum {value = (t == -1? -1:t + 1)};
    };

    //append
    template <class TList, class T> struct Append;
    //null
    template<>
    struct Append<NullType, NullType>{
        using Result = NullType;
    };
    template<typename T>
    struct Append<NullType, T>{
        using Result = TYPELIST_1(T);
    };
    //this is necessary, otherwise it will go to the above
    //this is necessary for append list with list
    template<typename Head, typename Tail>
    struct Append<NullType, Typelist<Head, Tail>> {
        using Result = Typelist<Head, Tail>;
    };
    //recurse
    template<typename Head, typename Tail, typename T>
    struct Append<Typelist<Head, Tail>, T>{
        using Result = Typelist<Head, typename Append<Tail, T>::Result>;
    };

    //erase the first occurence:
    template <class TList, class T> struct Erase;
    template <typename T> struct Erase<NullType, T> {
        using Result = NullType;
    };
    template <typename TList> struct Erase<TList, NullType> {
        using Result = TList;
    };
    template <typename Tail, typename T>
    struct Erase<Typelist<T, Tail>, T> {
        using Result = Tail;
    };
    template <typename Head, typename Tail, typename T>
    struct Erase<Typelist<Head, Tail>, T>{
        using Result = Typelist<Head, typename Erase<Tail, T>::Result>;
    };

    //erase all
    template <class TList, class T> struct EraseAll;
    template <typename T> struct EraseAll<NullType, T> {
        using Result = NullType;
    };
    template <typename TList> struct EraseAll<TList, NullType> {
        using Result = TList;
    };
    template <typename Tail, typename T>
    struct EraseAll<Typelist<T, Tail>, T> {
        using Result = typename EraseAll<Tail, T>::Result;
    };
    template <typename Head, typename Tail, typename T>
    struct EraseAll<Typelist<Head, Tail>, T>{
        using Result = Typelist<Head, typename EraseAll<Tail, T>::Result>;
    };

    //NoDuplicates
    template <class TList> struct NoDuplicates;
    template<> struct NoDuplicates<NullType>
    {
        using Result = NullType;
    };
    template<typename Head, typename Tail> struct NoDuplicates<Typelist<Head, Tail>>
    {
    private:
        using L1 = typename NoDuplicates<Tail>::Result;
        using L2 = typename Erase<L1, Head>::Result;
    public:
        using Result = Typelist<Head, L2>;
    };

    //replace first
    template <class TList, class T, class U> struct Replace;

    template <class T, class U>
    struct Replace<NullType, T, U>
    {
       using Result = NullType;
    };
    template <class T, class Tail, class U>
    struct Replace<Typelist<T, Tail>, T, U>
    {
       using Result = Typelist<U, Tail>;
    };
    template <class Head, class Tail, class T, class U> struct Replace<Typelist<Head, Tail>, T, U>
    {
       using Result = Typelist<Head, typename Replace<Tail, T, U>::Result>;
    };

    template <class TList, class T> struct MostDerived;
    template <class T>
    struct MostDerived<NullType, T>
    {
       typedef T Result;
    };
    template <class Head, class Tail, class T> struct MostDerived<Typelist<Head, Tail>, T> {
    private:
        using Candidate = typename MostDerived<Tail, T>::Result; 
    public:
        using Result = typename Tricks::Select< std::is_base_of<Candidate, Head>::value, Head, Candidate>::Result;
    };

    template <class T> struct DerivedToFront;
    template <>
    struct DerivedToFront<NullType>
    {
       using Result = NullType;
    };
    template <class Head, class Tail>
    struct DerivedToFront< Typelist<Head, Tail> > {
    private:
        using TheMostDerived = typename MostDerived<Tail, Head>::Result;
        using L = typename Replace<Tail, TheMostDerived, Head>::Result;
    public:
        using Result = Typelist<TheMostDerived, L>;
    };

    void demo(){
        using intdouble = TYPELIST_4(int, int, double, double);

        static_assert(Length<intdouble>::value == 4);

        static_assert(std::is_same<TypeAt<intdouble, 0>::Result, int>::value);
        static_assert(std::is_same<TypeAt<intdouble, 1>::Result, int>::value);
        static_assert(std::is_same<TypeAt<intdouble, 2>::Result, double>::value);
        static_assert(std::is_same<TypeAt<intdouble, 3>::Result, double>::value);
        //static_assert(std::is_same<TypeAt<intdouble, -1>::Result, double>::value);

        static_assert(IndexOf<intdouble, double>::value == 2);
        //static_assert(IndexOf<intdouble, double>::value == 3);

        using result = Append<intdouble, char>::Result;
        static_assert(IndexOf<result, char>::value == 4);

        //erase:
        static_assert(std::is_same<NullType, Erase<TYPELIST_1(int), int>::Result>::value);
        static_assert(std::is_same<TYPELIST_1(char), Erase<TYPELIST_2(int, char), int>::Result>::value);
        static_assert(std::is_same<TYPELIST_1(char), Erase<TYPELIST_1(char), int>::Result>::value);
        static_assert(std::is_same<TYPELIST_1(char), Erase<TYPELIST_2(char, int), int>::Result>::value);

        //erase all
        static_assert(std::is_same<TYPELIST_1(char), EraseAll<TYPELIST_3(int, char, int), int>::Result>::value);
        static_assert(std::is_same<NullType, EraseAll<TYPELIST_3(int, int, int), int>::Result>::value);
        static_assert(std::is_same<NullType, EraseAll<TYPELIST_1(int), int>::Result>::value);

        //no dup
        static_assert(std::is_same<TYPELIST_2(int, double), NoDuplicates<TYPELIST_4(int, double, int, double)>::Result>::value);
        static_assert(std::is_same<TYPELIST_1(int), NoDuplicates<TYPELIST_4(int, int, int, int)>::Result>::value);

        //replace:
        static_assert(std::is_same<TYPELIST_3(char, int, int), Replace<TYPELIST_3(double, int, int), double, char>::Result>::value);
    }
}


#endif