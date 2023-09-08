#include <iostream>

//Lets enummerate all things that support operator() in C++

// 1 - C like functions
// 2 - C pointers to function
// 3 - References to functions, that act like const pointers to functions. Somthing like this void(& func)() = Foo;
// 4 - Functors -> Objects that define operator()
// 5 - The result of applying operator.* or operator->* having a pointer to a member function in the right-hand side of the expression

// ONLY THESES objects in C++ allow to put a pair of parentheses to the right of any of the enumerated items, put an appropriate list of arguments inside, and get some processing done.

// The objects that support operator() are known as callable entities


//Example of some function pointers in old C style
// The compiler offers a syntactic shortcut: (*pF)() is equivalent to pF() . However, (*pF)() is more
// suggestive of what actually happens— pF is dereferenced, and the function-call operator () is applied to the
// dereferenced pointer.

void Foo();
void Bar();
int main()
{
// Define a pointer to a function that takes no
// parameters and returns void.
// Initialize that pointer with the address of Foo
void (*pF)() = &Foo;
Foo();
// Call Foo directly
Bar();
// Call Bar directly
(*pF)();
// Call Foo via pF
void (*pF2)() = pF;
// Create a copy of pF
pF = &Bar;
// Change pF to point to Bar
(*pF)();
// Now call Bar via pF
(*pF2)();
// Call Foo via pF2
}




void Foo(){
    std::cout << "Hola\n";
}

void Bar(){
    std::cout << "Adios\n";
}