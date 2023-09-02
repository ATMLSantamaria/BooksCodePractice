/* How would you search a typelist for a given type? Let's try to implement an IndexOf algorithm that
computes the index of a type in a typelist. If the type is not found, the result will be an invalid value, say -
1. The algorithm is a classic linear search implemented recursively. */

template<class T, class U>
struct TypeList
{
    typedef T Head;
    
    typedef U Tail;
};
class NullType{};

#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1,TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1,TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1,TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) TypeList<T1,TYPELIST_4(T2,T3,T4,T5)>

// IndexOf
// Inputs: Typelist TList , type T
// Output: Inner compile-time constant value
// If TList is NullType , then value is -1 .
// Else
// If the head of TList is T , then value is 0 .
// Else
// Compute the result of IndexOf applied to TList 's tail and T into a temporary
// value temp .
// If temp is -1 , then value is -1 .
// Else value is 1 plus temp .

//Remeber a partial specialization in compile time is equivalent to an if
//General
template<class TList, class T> 
struct IndexOf{};

//If TList is NullType
template<class T>
struct IndexOf<NullType,T>
{
    enum{value = -1};
};

//If Head if TList is T
//This match anything when the Head of the TypeList is T. Tail could be whatever
template<class T,class Tail>
struct IndexOf<TypeList<T,Tail>,T>
{
    enum{value=0};
};

template<class Head,class Tail,class T>
struct IndexOf<TypeList<Head,Tail>,T>
{
    private:
    enum{temp=IndexOf<Tail,T>::value};
    public:
    enum{value = (temp==-1) ? (-1) : (1+temp)}; //I write the parenthesis to make it more readable if in the future I come back here
};

class A{};class B{};class C{};class D{};class E{};class Z{};
typedef TYPELIST_5(B,A,C,E,D) RandomTypeList;

int index = IndexOf<RandomTypeList,E>::value; //Remeber this variable in global scope could cause collision with similar variable in other files
static int index2 = IndexOf<RandomTypeList,Z>::value; //With the static keyword the global scope is limited to this file

#include <iostream>
int main(){
    std::cout << index << std::endl;
    std::cout << index2 << std::endl; //-1 because Z is not in RandomTypeList
}



