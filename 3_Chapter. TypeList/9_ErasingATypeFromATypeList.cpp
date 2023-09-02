// Erasing a type from a typelist there are two options: Erase only the first
// occurrence, or erase all occurrences of a given type.
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
/* Erase
Input: Typelist TList , type T
Output: Inner type definition Result
If TList is NullType , then Result is NullType .
Else
If T is the same as TList::Head , then Result is TList::Tail .
Else Result is a typelist having TList::Head as its head and the result of applying
Erase to TList::Tail and T as its tail. */

//General
template <class TList,class T> struct Erase;
//If TList is NullType, then Result is NullType
template <class T> 
struct Erase<NullType,T>
{
    typedef NullType Result;
};
//If T is the same as Tlist;;HEad, then Result is Tlist::Tail
template<class Tail, class T>
struct Erase<TypeList<T,Tail>,T>
{
    typedef Tail Result;
};
//Else Result is a typelist having TList::HEad as its head and the result of applying Erase to TList::Tail and T
template<class Head,class Tail,class T>
struct Erase<TypeList<Head,Tail>,T>
{
    typedef TypeList<Head, typename Erase<Tail,T>::Result> Result;
};

//There is no default version of Erase, so it means that you cannot call it with certain types. Erase needs its first parameter to be a TypeList (or NULLType)



int main(){

}
