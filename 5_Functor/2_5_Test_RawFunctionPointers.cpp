#include "2_4_FunctorHandler.h"

#include <iostream>

// support for regular functions is already implemented out of the box because of two things: 
// 1 - the syntactic similarity between pointers to functions and functors 
// 2-  the type inference mechanism that C++ uses

//Explanation:
// The compiler sees a Functor constructed from TestFunction , it has no choice but to try the templated constructor.

// The compiler will then instantiate the template constructor with the template argument void (&)(int, double) , which is the type of TestFunction

// The type of fun_ in FunctorHandler is void (&)(int, double) as well

// When you invoke FunctorHandler<...>::operator() , it forwards to fun_() which is legal syntax for invoking a  through a pointer to function

//IMPORTANTE- > If you overload,yu will need to help the compiler to disambiguate
//You can notice how to try to create a Functor to an overload function does not compile if we dont make a extra help

// In presence of Overload there are two ways to identify a specific function: by using
// initialization (or an assignment) and by using a cast.

void TestFunction(int a, double b){
        std::cout << "TestFunction: ( " << a << " , "  << b << ") called" << std::endl;
    }

void TestFunctionOverload(int a, double b){
        std::cout << "TestFunctionOverload:( " << a << " , "  << b << ") called" << std::endl;
    }

void TestFunctionOverload(int a){
        std::cout << "TestFunctionOverload only int: ( " << a << " , "  << ") called" << std::endl;
    }


int main(){

    Functor<void,LOKI_TYPELIST_2(int,double)> command(&TestFunction);

    command(1,1.1);



    //Method 1 WITH OVERLOAD: USE INITIALISATION

    typedef void (*TpFun0)(int,double); 
    TpFun0 f;//compile exactly as  void (*f)(int,double)
    
    typedef   void      (*FunctionFunc)  ( );
    //         ^                ^         ^
    //     return type      type name  arguments


    void (*pf0)(int,double) = TestFunctionOverload;
    TpFun0 pf = TestFunctionOverload;
    //TpFun0 pf = &TestFunctionOverload; both version works 

    Functor<void, LOKI_TYPELIST_2(int, double)> commandFpr1(pf);
    commandFpr1(3, 3.3);
    Functor<void, LOKI_TYPELIST_2(int,double)> commandFpr0(pf0);
    commandFpr0(5,4);

    void (*pfUnico)(int) = TestFunctionOverload;
    Functor<void, LOKI_TYPELIST_1(int)> commandFprUnico(pfUnico);
    commandFprUnico(5);
    //Functor<void,LOKI_TYPELIST_2(int,double)> command2(&TestFunctionOverload);

    //METHOD 2 WITH OVERLOAD: USE A CAST
    Functor<void, LOKI_TYPELIST_2(int, double)> commandCast(static_cast<void (*)(int,double)>(TestFunctionOverload));

    commandCast(99,9999.87);



}