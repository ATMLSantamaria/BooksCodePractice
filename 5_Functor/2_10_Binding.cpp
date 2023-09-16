#include "2_4_FunctorHandler.h"


namespace Private
{
    template <class Fctor> struct BinderFirstTraits;

    template < typename R, class TList>
    struct BinderFirstTraits< Functor<R,TList>>
    {
        typedef typename Loki::TL::Erase<TList,
                typename Loki::TL::TypeAt<TList,0>::Result>::Result ParmList;
        typedef Functor<R,ParmList> BoundFunctorType;
        typedef typename BoundFunctorType::Impl Impl;
    };
}


template <class OriginalFunctor>
class BinderFirst : 
    public Private::BinderFirstTraits<OriginalFunctor>::Impl
{

    typedef typename Private::BinderFirstTraits<OriginalFunctor>::Impl Base;
    typedef typename OriginalFunctor::ResultType ResultType;

    typedef typename OriginalFunctor::Parm1 BoundType;

    typedef typename OriginalFunctor::Parm2 Parm1;
    typedef typename OriginalFunctor::Parm3 Parm2;
    typedef typename OriginalFunctor::Parm4 Parm3;
    typedef typename OriginalFunctor::Parm5 Parm4;
    typedef typename OriginalFunctor::Parm6 Parm5;
    typedef typename OriginalFunctor::Parm7 Parm6;
    typedef typename OriginalFunctor::Parm8 Parm7;
    typedef typename OriginalFunctor::Parm9 Parm8;
    typedef typename OriginalFunctor::Parm10 Parm9;
    typedef typename OriginalFunctor::Parm11 Parm10;
    typedef typename OriginalFunctor::Parm12 Parm11;
    typedef typename OriginalFunctor::Parm13 Parm12;
    typedef typename OriginalFunctor::Parm14 Parm13;
    typedef typename OriginalFunctor::Parm15 Parm14;
    typedef EmptyType Parm15; 

public:
    BinderFirst(const OriginalFunctor & f,BoundType bound):f_(f),bound_(bound){}

    BinderFirst * Clone() const 
    {
        return new BinderFirst(*this);
    }

    ResultType operator()()
    {
        return f_(bound_);
    }
    ResultType operator()(Parm1 p1)
    {
        return f_(bound_, p1);
    }
    ResultType operator()(Parm1 p1,Parm2 p2)
    {
    return f_(bound_, p1, p2);
    }

private:
    OriginalFunctor f_;
    BoundType bound_;
};

// The class template BinderFirst works in conjunction with the template function BindFirst. The
// merit of BindFirst is that it automatically deduces its template parameters from the types of the actual
// arguments that you pass it.



namespace Private
{
    template <class Fctor>
    typename BinderFirstTraits<Fctor>::BoundFunctorType BindFirst(const Fctor fun, typename Fctor::Parm1 bound)
    {
        typedef typename BinderFirstTraits<Fctor>::BoundFunctorType Outgoing;
        return Outgoing(std::auto_ptr<typename Outgoing::Impl>(new BinderFirst<Fctor>(fun,bound)));
    }
}

//Test
#include <iostream>
const char* Fun2(int i, int j)
{
    std::cout << "Fun2("   << i << ", " << j << ") called\n";
    return "0";
}
int main()
{

    //Functor needs Tom implement the copy constructor in order to work
    Functor<const char*, LOKI_TYPELIST_2(char, int)> f1(Fun2);
    Functor<std::string, LOKI_TYPELIST_1(double)> f2(Private::BindFirst(f1, 10));
    // Prints: Fun(10, 15) called
    f2(15);
}