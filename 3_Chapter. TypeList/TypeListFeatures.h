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
#define TYPELIST_6(T1,T2,T3,T4,T5,T6) TypeList<T1,TYPELIST_5(T2,T3,T4,T5,T6)>
#define TYPELIST_7(T1,T2,T3,T4,T5,T6,T7) TypeList<T1,TYPELIST_6(T2,T3,T4,T5,T6,T7)>

///              LENGTH

template<class TList> 
struct Length{}; //General case of Length

template<>//First specialization for matching the border case (NullType)
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

//////                     INDEX ACCESS
template <class TList, unsigned int index> struct TypeAt;

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

////////                           INDEX OF               
template<class TList, class T> 
struct IndexOf{};

//If TList is NullType
template<class T>
struct IndexOf<NullType,T>
{
    enum{value = -1};
};
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


//////////                          ERASE
template <class TList,class T> struct Erase;
template <class T> 
struct Erase<NullType,T>
{
    typedef NullType Result;
};
template<class Tail, class T>
struct Erase<TypeList<T,Tail>,T>
{
    typedef Tail Result;
};
template<class Head,class Tail,class T>
struct Erase<TypeList<Head,Tail>,T>
{
    typedef TypeList<Head, typename Erase<Tail,T>::Result> Result;
};