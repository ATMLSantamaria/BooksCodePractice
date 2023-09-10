#include "2_4_FunctorHandler.h"

#include <iostream>
#include <string>


void TestFunction(int a, double b){
        std::cout << "TestFunction: ( " << a << " , "  << b << ") called" << std::endl;
    }

void TestFunctionOverload(int a, double b){
        std::cout << "TestFunctionOverload:( " << a << " , "  << b << ") called" << std::endl;
    }

void TestFunctionOverload(int a){
        std::cout << "TestFunctionOverload only int: ( " << a << " , "  << ") called" << std::endl;
    }
//Anadimos una funcion que es convertida implicitamente en type and argumentspara ver si nuestro Functor es capaza de realizar estas 

const char * TestFunction_Conversion(double a, double b){
    static const char buffer[]= "Hola mundo\n";
    return buffer;
}

int main(){

    Functor<std::string,LOKI_TYPELIST_2(int,int)> command(&TestFunction_Conversion);
    //This functor define return type as string
    //And arguments 2 int

    //TestFunction_Conversion define return type as const char * and argument 2 doubles.

    //It should be bindable,we expect this to happen because int can be implicitly converted to double , and const char * is
    // implicitly convertible to string . If Functor does not accept the same conversions that C++ accepts,
    // Functor would be unnecessarily rigid.

    std::cout << command(1.1,1.1) << std::endl;




}