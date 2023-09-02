#include "TypeListFeatures.h"

// Erase
// Input: Typelist TList , type T
// Output: Inner type definition Result
// If TList is NullType , then Result is NullType .
// Else
// If T is the same as TList::Head , then Result is TList::Tail .
// Else Result is a typelist having TList::Head as its head and the result of applying
// Erase to TList::Tail and T as its tail.
template<class TList,class T>struct EraseAll;

template<class T>
struct EraseAll<NullType,T>
{
    typedef NullType Result;
};

template<class Tail,class T>
struct EraseAll<TypeList<T,Tail>,T>
{
    //// Go all the way down the list removing the type
    typedef typename EraseAll<Tail,T>::Result Result;
};

template<class Head,class Tail,class T>
struct EraseAll<TypeList<Head,Tail>,T>
{
    typedef TypeList<Head,typename EraseAll<Tail,T>::Result> Result;
};

typedef TYPELIST_6(int, int ,int, double,int,double) ListToErase;

typedef EraseAll<ListToErase,int>::Result ListErased;

//Check
int index = IndexOf<ListErased,int>::value;



#include <iostream>
int main(){
    std::cout << index << std::endl;
}