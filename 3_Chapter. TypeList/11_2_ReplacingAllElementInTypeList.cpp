#include "TypeListFeatures.h"
// Sometimes a replacement is needed instead of a removal. Replacing a type
// with another is an important building block for more advanced idioms.

// We need to replace type T with type U in a typelist TList .

//                      Algorithm
// ReplaceAll
// Inputs: Typelist TList , type T (to replace), and type U (to replace with)
// Output: Inner type definition Result
// If TList is NullType , then Result is NullType .
// Else
// If the head of the typelist TList is T , then Result is a typelist with U as its head and
//  recursively applies the algorithm to    TList::Tail as its tail.
// Else Result is a typelist with TList::Head as its head and the result of applying
// Replace to TList , T , and U as its tail.

template<class TList,class T,class U> struct ReplaceAll;

template<class T,class U>
struct ReplaceAll<NullType,T,U>
{
    typedef NullType Result;
};

template<class Tail,class T,class U>
struct ReplaceAll<TypeList<T,Tail>,T,U>
{
    typedef TypeList< U,typename ReplaceAll<Tail,T,U>::Result> Result;
};

template<class Head,class Tail, class T, class U>
struct ReplaceAll<TypeList<Head,Tail>,T,U>
{
    typedef TypeList<Head,typename ReplaceAll<Tail,T,U>::Result> Result;
};
    
class A{};
typedef TYPELIST_5(A,A,A,A,A) RandomTypeList;

//Lets Replace all A by int and then perform some operations to check the result

typedef ReplaceAll<RandomTypeList,A,int>::Result ReplacedTypeList;

int index = IndexOf<ReplacedTypeList,A>::value; //This index should be -1, since all A was replaced


#include <iostream>
int main(){
    std::cout << "index = "  << index << std::endl;

    //Now operation TypeAt to check that we really have an int there
    TypeAt<ReplacedTypeList,3>::Result integer=3;

    int toCheck=0;

    std::cout << "typeid().name() coming from TypeAt<ReplacedTypeList,3>::Result integer " << typeid(toCheck).name() << std::endl;
    std::cout << "typeid().name() coming from int toCheck " << typeid(integer).name() << std::endl;
    if(typeid(toCheck).name()==typeid(integer).name()){
        std::cout << "We know the in ReplacedTypeList all class A have been replaced by int";
        std::cout << "\nbecause when we use it to instantiate a object, such object has same type_info";
        std::cout << "\nthan a int created to check" << std::endl;
    }

    ++integer;

    std::cout << "integer = " << integer << std::endl;
    
}