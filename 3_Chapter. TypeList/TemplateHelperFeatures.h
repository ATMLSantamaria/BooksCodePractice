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

template <class T>
struct Type2Type
{
    typedef T OriginalType;
};

template <int v>
struct Int2Type
{
    enum { value = v };
};

template <typename T>
class TypeTraits
{
private:
    template <class U> struct PointerTraits
    {
        enum { result = false };
        typedef NullType PointeeType;
    };
    
    template <class U> struct PointerTraits<U*>
    {
        enum { result = true };
        typedef U PointeeType;
    };
    
    template <class U> struct ReferenceTraits
    {
        enum { result = false };
        typedef U ReferredType;
    };
    
    template <class U> struct ReferenceTraits<U&>
    {
        enum { result = true };
        typedef U ReferredType;
    };
    
    template <class U> struct PToMTraits
    {
        enum { result = false };
    };
    
    template <class U, class V>
    struct PToMTraits<U V::*>
    {
        enum { result = true };
    };

    template <class U> struct UnConst
    {
        typedef U Result;
        enum { isConst = 0 };
    };
    
    template <class U> struct UnConst<const U>
    {
        typedef U Result;
        enum { isConst = 1 };
    };

    template <class U> struct UnVolatile
    {
        typedef U Result;
        enum { isVolatile = 0 };
    };
    
    template <class U> struct UnVolatile<volatile U>
    {
        typedef U Result;
        enum { isVolatile = 1 };
    };

public:
    enum { isPointer = PointerTraits<T>::result };
    typedef typename PointerTraits<T>::PointeeType PointeeType;

    enum { isReference = ReferenceTraits<T>::result };
    typedef typename ReferenceTraits<T>::ReferredType ReferredType;
    
    enum { isMemberPointer = PToMTraits<T>::result };

    enum { isStdUnsignedInt = 
        TL::IndexOf<Private::StdUnsignedInts, T>::value >= 0 };
    enum { isStdSignedInt = 
        TL::IndexOf<Private::StdSignedInts, T>::value >= 0 };
    enum { isStdIntegral = isStdUnsignedInt || isStdSignedInt ||
        TL::IndexOf<Private::StdOtherInts, T>::value >= 0 };
    enum { isStdFloat = TL::IndexOf<Private::StdFloats, T>::value >= 0 };
    enum { isStdArith = isStdIntegral || isStdFloat };
    enum { isStdFundamental = isStdArith || isStdFloat || 
        Conversion<T, void>::sameType };
        
    enum { isUnsignedInt = isStdUnsignedInt || IsCustomUnsignedInt<T>::value };
    enum { isSignedInt = isStdSignedInt || IsCustomSignedInt<T>::value };
    enum { isIntegral = isStdIntegral || isUnsignedInt || isSignedInt };
    enum { isFloat = isStdFloat || IsCustomFloat<T>::value };
    enum { isArith = isIntegral || isFloat };
    enum { isFundamental = isStdFundamental || isArith || isFloat };
    
    typedef typename Select<isStdArith || isPointer || isMemberPointer,
        T, typename Private::AddReference<T>::Result>::Result ParameterType;
    
    enum { isConst = UnConst<T>::isConst };
    typedef typename UnConst<T>::Result NonConstType;
    enum { isVolatile = UnVolatile<T>::isVolatile };
    typedef typename UnVolatile<T>::Result NonVolatileType;
    typedef typename UnVolatile<typename UnConst<T>::Result>::Result 
        UnqualifiedType;
};
    

// template<class T,class U>
// T * Create(const U& arg,Type2Type<T>){
//     return new T(arg);
// }
// template<class U>
// Widget * Create(const U & arg,Type2Type<Widget>){
//     return new Widget(arg,-1);
// }



