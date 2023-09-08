#include <iostream>
#include <typeinfo>

void f(int i, char c)
{
    std::cout << i << ' ' << c << std::endl;
}

int main()
{
    std::cout << typeid(f).name() << std::endl; //FvicE
    f(0, '1');

    void (*pf)(int, char) (&f); //ugly
    std::cout << typeid(pf).name() << std::endl; //PFvicE
    (*pf)(2, '3');
    pf(4, '5'); //works, but I don't recommend it

    void (&rf)(int, char) (f); //still ugly
    std::cout << typeid(rf).name() << std::endl; //FvicE
    rf(6, '7');

    auto &af (f); //pretty, but only works in C++11
    std::cout << typeid(af).name() << std::endl; //FvicE, same as above
    af(8, '9');
}