#include <iostream>
#include <vector>
#include <deque>

/*
A templated stack with two parameter: data type and container type.
*/
namespace stack6dec1 {
    template <typename T, typename CONT=std::deque<T>>
    class Stack{
    private:
        CONT elems;
    public:
        Stack();
        void push(T const&);
        T pop();
        T top() const;
        bool empty() const {
            return elems.empty();
        }
        template <typename T2, typename CONT2>
        Stack<T, CONT>& operator=(Stack<T2, CONT2> const&);
        void dump(){
          for(auto it = elems.begin(); it!=elems.end(); ++it){
            std::cout << *it << std::endl;
          }
        }
    };

    template <typename T, typename CONT>
    Stack<T, CONT>::Stack(){;};

    template <typename T,typename  CONT>
    void Stack<T, CONT>::push(T const& elem){
        this->elems.push_back(elem);
    };

    template <typename T, typename CONT>
    T Stack<T, CONT>::pop(){
        if(this->empty()){
            throw std::out_of_range("Stack<>::pop(): stack is empty");
        }
        T ret = this->elems.back();
        this->elems.pop_back();
        return ret;
    }

    template <typename T, typename CONT>
    T Stack<T, CONT>::top() const{
        if(this->empty()){
            throw std::out_of_range("Stack<>::pop(): stack is empty");
        }
        return this->elems.back();
    }

    template <typename T, typename CONT>
    template <typename T2, typename CONT2>
    Stack<T, CONT>& Stack<T, CONT>::operator=(Stack<T2, CONT2> const& rhs){
        if((void*)this == (void*)&rhs){
            return *this;
        }
        this->elems.clear();
        /* you can't do this (why?)
         as different types cannot access private members
        for(auto it = rhs.elems.begin(); it!=rhs.elems.end(); ++it){
            this->elems.push_back(*it);
        }
         */
        // ctor?
        Stack<T2, CONT2> tmp(rhs);
        while(!tmp.empty()){
          elems.push_back(tmp.top());
          tmp.pop();
        }
        return *this;
    }
    void demo(){
        std::cout << "starting demo stack6dec1" << std::endl;
        stack6dec1::Stack<double, std::deque<double> > s4;
        std::cout << "ending demo stack6dec1" << std::endl;
    }
}
