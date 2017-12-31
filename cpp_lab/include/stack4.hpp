#include <iostream>
#include <vector>
#include <deque>

namespace stack4{
    template <typename T, int MAXSIZE>
    class Stack{
    private:
        T elems[MAXSIZE];
        int numElems;
    public:
        Stack();
        void push(T const&);
        T pop();
        T top() const;
        bool empty() const {
            return numElems == 0;
        }
        bool full() const {
            return numElems == MAXSIZE;
        }
    };
    
    template <typename T, int MAXSIZE>
    Stack<T, MAXSIZE>::Stack(): numElems(0){;};
    
    template <typename T, int MAXSIZE>
    void Stack<T, MAXSIZE>::push(T const& elem){
        if(this->full()) {
            throw std::out_of_range("Stack<>::push(): stack is full");
        }
        this->elems[this->numElems] = elem;
        this->numElems++;
    };
    
    template <typename T, int MAXSIZE>
    T Stack<T, MAXSIZE>::pop(){
        if(this->empty()){
            throw std::out_of_range("Stack<>::pop(): stack is empty");
        }
        T ret = this->elems[this->numElems];
        this->numElems--;
        return ret;
    }
    
    template <typename T, int MAXSIZE>
    T Stack<T, MAXSIZE>::top() const{
        if(this->empty()){
            throw std::out_of_range("Stack<>::pop(): stack is empty");
        }
        return this->elems[this->numElems - 1];
    } 
    void demo(){
        std::cout << "starting demo stack4" << std::endl;
        stack4::Stack<int, 10> s;

        s.push(10);
        s.pop();
        std::cout << "starting demo stack4" << std::endl;
    }
}
