/* Having access by index to the elements of a typelist would certainly be a desirable feature. It would
linearize typelist access, making it easier to manipulate typelists comfortably. Of course, as with all the
entities we manipulate in our static world, the index must be a compile-time value */
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

//Access of a template for a indexed operation would look like this

template <class TList, unsigned int index> struct TypeAt;

/*             Algorithm
TypeAt
Inputs: Typelist TList , index i
Output: Inner type Result
If TList is non-null and i is zero, then Result is the head of TList .
Else
If TList is non-null and index i is nonzero, then Result is obtained by applying
TypeAt to the tail of TList and i-1 .
Else there is an out-of-bound access that translates into a compile-time error. 
*/

//Working in compile time partial specialization of templates correspond to if-else in run time. Therefore I need a partial specialization for each case

template<class Head,class Tail>
struct TypeAt<TypeList<Head,Tail>,0>
{
    typedef Head Result; //a type name  can be seen as a type name constant (since in compile time eveything is inmutable)
};

template<class Head, class Tail, unsigned int i>
struct TypeAt<TypeList<Head, Tail>, i>
{
    typedef typename TypeAt<Tail,i-1>::Result Result;
};

typedef TYPELIST_4(NullType,NullType,double,NullType) ListToCheck;
#include <iostream>
int main(){

    TypeAt<ListToCheck,2>::Result VariableToCheck; //At compile time nthe double has been selected
    
    VariableToCheck = 2; //At run time

    std::cout << VariableToCheck << std::endl;

    //Easy to check that if we choose other index the type choosen is NullType and therefore we cant assign since NullType does not support this operation
    TypeAt<ListToCheck,1>::Result NullToCheck; //NullType choosen at compile time
    //NullToCheck=0;




}


