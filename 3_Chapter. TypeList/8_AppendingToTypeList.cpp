//A mechanism to append Types (or TypeList) to a TypeList

//But remember that a TypeList is not modifiable

//We need to return "by value" a new TypeList
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

//                                         ALGORITHM
// Append
// Inputs: Typelist TList , type or typelist T
// Output: Inner type definition Result
// If TList is NullType and T is NullType , then Result is NullType .
// Else
// If TList is NullType and T is a single (nontypelist) type, then Result is a typelist hav-
// ing T as its only element.
// Else
// If TList is NullType and T is a typelist, Result is T itself.
// Else if TList is non-null, then Result is a typelist having TList::Head as its
// head and the result of appending T to TList::Tail as its tail.
template<class TList,class T> struct Append;

//First if -> TList is NullType and T is NullType
template<>
struct Append<NullType,NullType>
{
    typedef NullType Result; //With this typedef we create the Result type
};
//Second if -> TList is NullType and T is a single Type
template<class T>
struct Append<NullType,T>
{
    typedef TYPELIST_1(T) Result; //We create a TypeList of 1 element with T
};
//Third if -> TList is NullType and T is a TypeList. result is T itself
template<class Head,class Tail>
struct Append<NullType,TypeList<Head,Tail>>
{
    typedef TypeList<Head,Tail> Result;
};
//Fourth if -> TList is non-null, then Result is a typelist having TList::Head as its head and the result of appending T to TList::Tail as its tail.
template<class Head,class Tail, class T>
struct Append<TypeList<Head,Tail>,T>
{
    typedef TypeList<Head, typename Append<Tail,T>::Result> Result;
};

//I will append two typeList and then use the previous feature to search the index

///    Search Functionality
template<class TList, class T> struct IndexOf{};
template<class T> struct IndexOf<NullType,T>
{
    enum{value = -1};
};
template<class T,class Tail> struct IndexOf<TypeList<T,Tail>,T>
{
    enum{value=0};
};
template<class Head,class Tail,class T>struct IndexOf<TypeList<Head,Tail>,T>
{
    private:
    enum{temp=IndexOf<Tail,T>::value};
    public:
    enum{value = (temp==-1) ? (-1) : (1+temp)}; 
};
/// 
class A{};class B{};class C{};class D{};class E{};class F{};class G{};class H{};class I{};class J{};class K{};class Z{};

typedef TYPELIST_4(A,B,C,D) TypeList1;
typedef TYPELIST_4(E,F,G,H) TypeList2;

typedef Append<TypeList1,TypeList2>::Result ComposedTypeList;
int index = IndexOf<ComposedTypeList,G>::value;

//We can also use Append to append typelist created in the moment
typedef TYPELIST_4(signed char,short int, int, long int) SignedIntegers;

//We can create a SignedTypes Using Append
typedef Append<SignedIntegers,TYPELIST_3(float,double,long double)>::Result SignedTypes;

#include <iostream>
int main(){
    std::cout << index << std::endl;
}
