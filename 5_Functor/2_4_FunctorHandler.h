#include "../loki-0.1.7/include/loki/Typelist.h"
#include <memory>
class NullType{};
struct EmptyType{};

//We for handling other functors we need something like:
//template <class Fun>
//Functor(const Fun & fun);


//First a TypeAt template operation to find a position in a TypeList
template<class TList, unsigned int index,typename DefaultType=NullType>
struct TypeAtNonStrict
{
    typedef DefaultType Result; //index not found
};
template<class Head,class Tail, typename DefaultType>
struct TypeAtNonStrict<Loki::Typelist<Head,Tail>,0,DefaultType>
{
    typedef Head Result; //When index is 0 the Result is Head
};
template<class Head,class Tail,unsigned int index,typename DefaultType>
struct TypeAtNonStrict<Loki::Typelist<Head,Tail>,index,DefaultType>
{
    typedef typename TypeAtNonStrict<Tail,index-1,DefaultType>::Result Result;
};

//Declaration of this template here is necessary
template<typename R,class TList>
class FunctorImpl;

//forward declaration of FunctorHandler
template <class ParentFunctor,typename Fun>
class FunctorHandler;



template <typename R,class TList>
class Functor
{   
    public:
    typedef R ResultType;
    typedef FunctorImpl<R,TList> Impl;
    typedef TList ParmList;
    typedef typename TypeAtNonStrict<TList,0,EmptyType>::Result Parm1;
    typedef typename TypeAtNonStrict<TList,1,EmptyType>::Result Parm2;
    typedef typename TypeAtNonStrict<TList,2,EmptyType>::Result Parm3;
    typedef typename TypeAtNonStrict<TList,3,EmptyType>::Result Parm4;
    typedef typename TypeAtNonStrict<TList,4,EmptyType>::Result Parm5;
    typedef typename TypeAtNonStrict<TList,5,EmptyType>::Result Parm6;
    typedef typename TypeAtNonStrict<TList,6,EmptyType>::Result Parm7;
    typedef typename TypeAtNonStrict<TList,7,EmptyType>::Result Parm8;
    typedef typename TypeAtNonStrict<TList,8,EmptyType>::Result Parm9;
    typedef typename TypeAtNonStrict<TList,9,EmptyType>::Result Parm10;
    typedef typename TypeAtNonStrict<TList,10,EmptyType>::Result Parm11;
    typedef typename TypeAtNonStrict<TList,11,EmptyType>::Result Parm12;
    typedef typename TypeAtNonStrict<TList,12,EmptyType>::Result Parm13;
    typedef typename TypeAtNonStrict<TList,13,EmptyType>::Result Parm14;
    typedef typename TypeAtNonStrict<TList,14,EmptyType>::Result Parm15;

   
    public:
    R operator()(){
        return (*_spImpl)();
    }
    R operator()(Parm1 p1){
        return (*_spImpl)(p1);
    }
    R operator()(Parm1 p1 ,Parm2 p2){
        return (*_spImpl)(p1,p2);
    }


    private:
    // typedef FunctorImpl<R,TList> Impl;
    std::auto_ptr<Impl> _spImpl; //auto_ptr deprecated but so far I prefer to follow the book  
    
    public:
    Functor(){};
    Functor(const Functor&); //Copy constructor
    Functor & operator=(const Functor&);//copy assignment operator
    explicit Functor(std::auto_ptr<Impl>spImpl) ;  

    //Constructor that takes any functor object
    template<typename Fun>
    Functor(const Fun& fun);
};


//Now using the Functor handler we can write the templated Constructor of Functor
template<typename R,class TList> //stands for the template class Functor
template<typename Fun> //stands for a member function template of the template class Functor. In this case the constructor
Functor<R,TList>::Functor(const Fun & fun):_spImpl(new FunctorHandler<Functor,Fun>(fun))
{
    //_spImpl is a auto_ptr<FunctorImpl<R,TList>. FunctorHandler inherit from FunctorImpl<R,TList> 
    //Therefore it can be placed there
}
// In standardese, this type of code is known as an "out-of-
// class member template definition."





//Partial specialisation for no parameter
template <typename R>
class FunctorImpl<R,Loki::NullType>
{
    public:
    virtual R operator()()=0; // pure virtual operator() that takes no argument and return a R
    virtual FunctorImpl * Clone() const = 0; //recuerda que const promete no modificar el objecto functor que lo invoque. functor1.Clone(); nunca modifica a functor 1. Por tanto si functor1 es const se puede utilizar en el
    virtual ~FunctorImpl(){}
};  

//Partial specialisation for 1 parameter
template<typename R,typename P1>
class FunctorImpl<R,LOKI_TYPELIST_1(P1)>
{
    public:
    virtual R operator()(P1)=0;
    virtual FunctorImpl * Clone() const = 0;
    virtual ~FunctorImpl(){}
};

//Partial specialisation for 2 parameter
template<typename R, typename P1, typename P2>
class FunctorImpl<R,LOKI_TYPELIST_2(P1,P2)>
{
    public:
    virtual R operator()(P1,P2)=0;
    virtual FunctorImpl * Clone() const = 0;
    virtual ~FunctorImpl(){}
};

template<typename R, typename P1, typename P2,typename P3>
class FunctorImpl<R,LOKI_TYPELIST_3(P1,P2,P3)>
{
    public:
    virtual R operator()(P1,P2,P3)=0;
    virtual FunctorImpl * Clone()const = 0;
    virtual ~FunctorImpl(){}
};


// To implement this constructor we need a simple class template FunctorHandler derived from
// FunctorImpl<R, TList> . That class stores an object of type Fun and forwards operator() to it.
// We resort to the same trick as in the previous section for implementing operator() properly.

// To avoid defining too many template parameters for FunctorHandler , we make the Functor
// instantiation itself a template parameter. This single parameter collects all the others because it provides
// inner typedef s.

template <class ParentFunctor,typename Fun>
class FunctorHandler : public FunctorImpl <typename ParentFunctor::ResultType, typename ParentFunctor::ParmList>
{
    public:
    typedef typename ParentFunctor::ResultType ResultType;

    FunctorHandler(const Fun & fun):fun_(fun){}

    FunctorHandler * Clone() const { //clone this Functor handler
        return new FunctorHandler(*this); //2 functor handlers point to same function (or in this case to the same functor). With function this is logical since you want to have handlers
        //to some function. It is not like pointers to data that can create crashes when deallocate
    }

    ResultType operator()(){
        return fun_(); //call the operator() of the Functor
    }
    ResultType operator()(typename ParentFunctor::Parm1 p1){
        return fun_(p1); //call the operator() of the Functor
    }
    ResultType operator()(typename ParentFunctor::Parm1 p1,typename ParentFunctor::Parm2 p2){
        return fun_(p1,p2); 
    }
    ResultType operator()(typename ParentFunctor::Parm1 p1,typename ParentFunctor::Parm2 p2,typename ParentFunctor::Parm3 p3){
        return fun_(p1,p2,p3); 
    }

    private:
    Fun fun_;
};

// FunctorHandler looks much like Functor itself: It forwards requests to a stored member variable.
// The main difference is that the functor is stored by value, not by pointer. This is because, in general,
// functors are meant to be this way—nonpolymorphic types with regular copy semantics.




// int main(){

// }