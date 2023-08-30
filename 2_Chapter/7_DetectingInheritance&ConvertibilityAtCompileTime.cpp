//To know in compile time Inheritance relation and Convertivility allows us to avoid using dynamic_cast at runtime, that is costly from performance point of view.

class U{
    int a;
};
class T:public U{
    //int b;
};
class T_NoConvertible{
    int c;
    double d;
};
//Conversion detection relies on sizeof in conjunction with overload functions.

// 1 - We provide 2 overloads of a functions. One accept the type to convert to (U) and other accept anything else.

// 2 - We call the overload function with a temporary of type (T), the type whose convertability we want to determine.

// 3 - If the function that accepts the U is called, we know that T is convertible to U. If the other is called, T is not convertible.

// 4 - To detect which function is called we arrange the 2 overloads to return types of different sizes, and then we discriminate with sizeof.
// Power of sizeof -> 
// You can apply sizeof to any expression, no matter how complex, and sizeof returns its size
// without actually evaluating that expression at runtime.

// 5 - E.G. in theory char and long double should have different sizes, but that is not guaranteed by the standard. 
// So for this we this little scheme

typedef char Small;
class Big{char dummy[3];};

//By definition size of Small is 1, and size of Big is unknown but greater than 1.

//6 - We need the 2 overloads. One should accept a U and return a Small (for example)

Small Test(U);

//How to write a function that accepts anything else?

Big Test(...);
/*
(Passing a C++ object to a function with ellipses has undefined results, but this doesn't matter. Nothing
actually calls the function. It's not even implemented. Recall that sizeof does not evaluate its argument.)
 */

//Now lets try this
//Remember, when we apply Test to a Type T, if T is compatible with U, the Small Test(U); should be called
#include <iostream>

int main(){
    //The next expression will not compile if the Constructor is private
    //const bool conv_Exist= sizeof(Test(T))==sizeof(Small);
    //We can use this, a expression that will never be evaluated but is enough for sizeof to understand the size
    T MakeT();
    const bool conv_Exist=sizeof(Test(MakeT()))==sizeof(Small);

    if (conv_Exist){
        std::cout << "The tipe is compatible\n";
    }else {
        std::cout << "The tipe is NOT compatible\n";
    }

    T_NoConvertible Make_NC();
    const bool conv_Exist2=sizeof(Test(Make_NC()))==sizeof(Small);

    if (conv_Exist2){
        std::cout << "The tipe is compatible\n";
    }else {
        std::cout << "The tipe is NOT compatible\n";
    }

}