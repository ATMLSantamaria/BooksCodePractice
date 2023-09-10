#include "2_4_FunctorHandler.h"

#include <iostream>

//Test to the implemented Functor class. Now it is able to handle functors
//Nota: recuerda que un functor es simplemente una clase que implementa el operador()
struct TestFunctor{
    void operator()(int a, double b){
        std::cout << "TestFunctor operator(): " << a << " , "  << b << std::endl;
    }
};

int main(){
    TestFunctor f;
    Functor<void,LOKI_TYPELIST_2(int,double)> command(f);
    Functor<void,LOKI_TYPELIST_2(int,double)> command2(f);

    command(4,8.8);

    command2(5,9.9);

    command(1,1.1);


}