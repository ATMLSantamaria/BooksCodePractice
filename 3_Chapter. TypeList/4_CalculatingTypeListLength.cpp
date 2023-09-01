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

/*
    Given a typelist TList , obtain a compile-time constant that evaluates its length.
    The constant ought to be a compile-time one because typelists are static constructs, so we'd expect all
    calculations related to typelists to be performed at compile time.
 */

// The idea behind template manipulations is to exploit recursive templates, which are templates that use instatiations
// of themselves as part of their definition

//While doing this they pass a different template argument list. Recursion is stopped with a explicit specialization for a border case

template<class TList> 
struct Length{}; //General case of Length

//First specialization for matching the border case (NullType)
template<>
struct Length<NullType>
{
    enum {value=0}; //Meaning -> Length for the NullType is 0
};

//Second partial specialization to match any TypeList

//Recordemos T es Head y U Tail. Por eso necesitamos sumar el valor de longitud de tale
template<class T, class U>
struct Length<TypeList<T,U>>
{
    enum {value=1+Length<U>::value};
};

int main(){

}