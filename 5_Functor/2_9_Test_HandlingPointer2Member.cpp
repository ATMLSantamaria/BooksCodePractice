

#include "2_4_FunctorHandler.h"

#include <iostream>

#include <iostream>
class Parrot
{
    public:
    void Eat(int a, double calories_per_nut)
    {
        std::cout << "tasty" << a << "nuts" << "tasty" << a*calories_per_nut << "calories\n";
    }
    void Speak()
    {
        std::cout << "I am the master of my fate, I am the captain of my soul\n";
    }
};

int main() {
    

    Parrot geronimo;

    Functor<void,LOKI_TYPELIST_2(int,double)> cmd1(&geronimo,&Parrot::Eat);
    // cmd2(&geronimo,&(Parrot::Eat));

    cmd1(2,90);

    



}

