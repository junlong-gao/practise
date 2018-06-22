# CPP-LAB
A repo hold various notes and examples on C++(11 + k) features, where k = 3i.

## List of References:
1. cpl : "The C++ Programming Language, 4th Edition"
2. mcppd: "Modern C++ Design: Generic Programming and Design Pattern Applied"
3. ospp: "Operating Systems: Principles and Practice"
4. emcpp: "Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14"
5. cppt: "C++ Templates: The Complete Guide"

## ```sptr.cpp```
Smart pointers, see emcpp.
* ```std::shared_ptr```
* ```std::weak_ptr```
* ```std::unique_ptr```

## ```msem.cpp```
Move semantics, see emcpp
* Copy elision and binding
* Perfect forwarding
* Rvalue reference
* Special rvalue type deduction
* Reference collapsing

## ```concurrency.cpp```
Lambda expressions and concurrency programming, see ospp
* Lambda expressions and init capture
* Lambda templates
* Thread, mutex and condition variables
* High level sync objects: Read/Write Lock, BoundedBuffer, Memory Barrier

## ```stack*.hpp```
The template system via stack demo. See cppt.

## ```Policy.hpp```
Policy based design pattern.

## ```Tricks.hpp```
See Chapter 2, in mcppd

## ```typelist.hpp```