template<class T, class U>
class Conversion{
    typedef char Small;
    class Big{char dummy[2];};

    //Overload functions to return different types in function of the possibility of conversion of T into U
    static Small Test(U);
    static Big Test(...);

    //Function necessary to use T in case its constructor is private
    static T MakeT();

    public:
    enum{exists=
         sizeof( Test(MakeT())) == sizeof(Small) };

    enum { sameType = false };
};

//We implement a partial specialization of Conversion
template<class T>
class Conversion<T,T>{
    public:
    enum{exists=1,sameType=1};
};

//Now we have the general class to check the conversion, and also the partial specialisation for the case where the 2 types are identical
//Now is very easy to determine inheritance
#define SUPERSUBCLASS(T,U) \
    (Conversion<const U* ,const T* >::exists && \
    !Conversion<const T* ,void *>::sameType) 


//Select
//Uses a boolean passed as argument template and a partial specialisation in false to decide between 2 types
template<bool flag,typename T,typename U>
struct Select
{
    typedef T Result;
};
template<typename T,typename U>
struct Select<false,T,U>
{
    typedef U Result;
};




