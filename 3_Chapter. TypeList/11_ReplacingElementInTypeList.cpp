#include "TypeListFeatures.h"
// Sometimes a replacement is needed instead of a removal. Replacing a type
// with another is an important building block for more advanced idioms.

// We need to replace type T with type U in a typelist TList .

//                      Algorithm
// Replace
// Inputs: Typelist TList , type T (to replace), and type U (to replace with)
// Output: Inner type definition Result
// If TList is NullType , then Result is NullType .
// Else
// If the head of the typelist TList is T , then Result is a typelist with U as its head and
// TList::Tail as its tail.
// Else Result is a typelist with TList::Head as its head and the result of applying
// Replace to TList , T , and U as its tail.

//General Definition
template<class TList,class T, class U> struct Replace;

//If Tlist is NullType , then Result is NullType .
template<class T,class U>
struct Replace<NullType,T,U>{
    typedef NullType Result;
};

//If the head of the typelist TList is T , then Result is a typelist with U as its head and
// TList::Tail as its tail
template<class Tail,class T,class U>
struct Replace<TypeList<T,Tail>,T,U>
{
    typedef TypeList<U,Tail> Result;
};

//Else Result is a typelist with TList::Head as its head and the result of applying
// Replace to TList , T , and U as its tail.
template<class Head,class Tail,class T,class U>
struct Replace<TypeList<Head,Tail>,T,U>
{
    typedef TypeList<Head,typename Replace<Tail,T,U>::Result> Result;
};



typedef TYPELIST_5(double,double,int,double,double) TargetTypeList;
typedef Replace<TargetTypeList,int,float>::Result ResultTypeList;

class A{};class B{};class C{};class D{};class E{};class Z{};
typedef TYPELIST_5(B,A,C,E,D) RandomTypeList;

int index = IndexOf<RandomTypeList,E>::value;

// class A{};  
int a = IndexOf<ResultTypeList,int>::value;
int b = IndexOf<ResultTypeList,float>::value;

#include <iostream>
int main(){
    std::cout << " Index o a sera -1 porque int ha sido reemplazado por float. index=" << a << std::endl;
    std::cout << " Index de float. b = " << b << std::endl;


}


