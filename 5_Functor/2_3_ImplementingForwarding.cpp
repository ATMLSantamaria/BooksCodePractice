#include "../loki-0.1.7/include/loki/Typelist.h"
#include <memory>
class NullType{};
struct EmptyType{};
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



template <typename R,class TList>
class Functor
{
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
    //We implement all operators. For a given Functor instantiation,only one is correct (and it is called) in each case, but
    //we know that the compiler only generate code for the one that is 
    //called . Therefore there is no issue with the others
    R operator()(){
        return (*_spImpl)();
    }
    R operator()(Parm1 p1){
        return (*_spImpl)(p1);
    }
    R operator()(Parm1 p1 ,Parm2 p2){
        return (*_spImpl)(p1,p2);
    }


    //Explained in 2_2
    private:
    typedef FunctorImpl<R,TList> Impl;
    std::unique_ptr<Impl> _spImpl; //auto_ptr deprecated but so far I prefer to follow the book  
    
    public:
    Functor(){};
    Functor(const Functor&); //Copy constructor
    Functor & operator=(const Functor&);//copy assignment operator
    //Functor & operator=(int i); //un overload cualquiera a assingment operator
    explicit Functor(std::unique_ptr<Impl>spImpl) ;   

};




//Partial specialisation for no parameter
template <typename R>
class FunctorImpl<R,Loki::NullType>
{
    public:
    virtual R operator()()=0; // pure virtual operator() that takes no argument and return a R
    virtual FunctorImpl * Clone() const; //recuerda que const promete no modificar el objecto functor que lo invoque. functor1.Clone(); nunca modifica a functor 1. Por tanto si functor1 es const se puede utilizar en el
    virtual ~FunctorImpl(){}
};  

//Partial specialisation for 1 parameter
template<typename R,typename P1>
class FunctorImpl<R,LOKI_TYPELIST_1(P1)>
{
    public:
    virtual R operator()(P1)=0;
    virtual FunctorImpl * Clone() const;
    virtual ~FunctorImpl(){}
};

//PArtial speciaölisation for 2 parameter
template<typename R, typename P1, typename P2>
class FunctorImpl<R,LOKI_TYPELIST_2(P1,P2)>
{
    public:
    virtual R operator()(P1,P2)=0;
    virtual FunctorImpl * Clone() =0;
    virtual ~FunctorImpl(){}
};


// Define a Functor that accepts an int and a double and
// returns a double.
 Functor<double, LOKI_TYPELIST_2(int, double)> myFunctor;
// Invoke it.
// operator()(double, int) is generated.
double result = myFunctor(4, 5.6);
// Wrong invocation.
//double result = myFunctor(); // error!
// operator()() is invalid because
// FunctorImpl<double, TYPELIST_2(int, double)>
// does not define one.







int main(){

}