#include <iostream>

class Parrot
{
    public:
    void Eat()
    {
        std::cout << "tasty,tasty\n";
    }
    void Speak()
    {
        std::cout << "I am the master of my fate, I am the captain of my soul\n";
    }
};

int main()
{
    // Define a type: pointer to a member function of
    // Parrot, taking no arguments and
    // returning void.

    typedef void (Parrot::* TpMemFun)();

    void (Parrot::*ptr)(void); //Create a pointer to member function withour typdef

    // Create an object of that type
    // and initialize it with the address of
    // Parrot::Eat.

    TpMemFun pActivity = &Parrot::Eat;

    ptr = &Parrot::Speak;

    //Create a parrot
    Parrot geronimo;
    //And a pointer to it
    Parrot * pGeronimo = &geronimo;

    // Invoke the member function stored in Activity
    // via an object. Notice the use of operator.*

    (geronimo.*pActivity)();

    // Same, via pointer. Now we use operator->*
    (pGeronimo->*pActivity)();

    // Change the activity
    pActivity = &Parrot::Speak;
    // Wake up, Geronimo!
    (geronimo.*pActivity)();


    (geronimo.*ptr)();
}