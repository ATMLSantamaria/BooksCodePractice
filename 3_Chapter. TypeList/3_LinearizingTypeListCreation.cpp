//This definition of TypeList could be to messy or strange

template<class T, class U>
struct TypeList
{
    typedef T Head;
    
    typedef U Tail;
};
class NullType{};

//For example lets imagine we want a typelist of the integral types
typedef TypeList<signed char,TypeList<short int,TypeList<int,TypeList<long int, NullType> > > > SignedIntegers;

//In order to linearize the TypeList creation we can create a series of MACROS that transform recursion into simple enumeration, in this way is done in the
// Loki library. The idea is the next, the repetitive code is store in the library header and scales the typelist to a large library defined number
//(in the case of Loki to 50)

#define TYPELIST_1(T1) TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TypeList<T1,TYPELIST_1(T2)>
#define TYPELIST_3(T1,T2,T3) TypeList<T1,TYPELIST_2(T2,T3)>
#define TYPELIST_4(T1,T2,T3,T4) TypeList<T1,TYPELIST_3(T2,T3,T4)>
#define TYPELIST_5(T1,T2,T3,T4,T5) TypeList<T1,TYPELIST_4(T2,T3,T4,T5)>
#define TYPELIST_6(T1,T2,T3,T4,T5,T6) TypeList<T1,TYPELIST_5(T2,T3,T4,T5,T6)>
#define TYPELIST_7(T1,T2,T3,T4,T5,T6,T7) TypeList<T1,TYPELIST_6(T2,T3,T4,T5,T6,T7)>

//And so on. In our case we limit to a TypeList of maximum 7 elements

//Now to create a TypeList to the previou one of SignedIntegers become nicer
typedef TYPELIST_4(signed char,short int, int, long int) SignedIntegersNicer;


//Now that create TypeList is simple we can check the TypeList manipulation is awkward. For example to access to the last element of the TypeList
SignedIntegersNicer::Tail::Tail::Head a;

#include <iostream>
int main(){
    //a is a long ing. We can use the Type definded in the TypeList to give type to an object
    SignedIntegersNicer::Tail::Tail::Head integerComingFromTypeList;
    integerComingFromTypeList=7;
    std::cout << integerComingFromTypeList << std::endl;

}