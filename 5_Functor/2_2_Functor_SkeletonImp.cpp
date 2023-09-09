#include "../LokiIncludes.h"
#include <memory>
// The polymorphic class FunctorImpl , wrapped by Functor , has the same template parameters as Functor

template<typename R,class TList>
class FunctorImpl;

// FunctorImpl defines a polymorphic interface that abstracts a function call. For each number of
// parameters, we define a FunctorImpl explicit specialization Each specialization defines
// a pure virtual operator() for the appropriate number and types of parameters.

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
    virtual R operator()(P1,P2)=0;
    virtual FunctorImpl * Clone() =0;
    virtual ~FunctorImpl(){}
};
// 1 - Purpose of Clone is the creation of a polymorphic copy of the FunctorImpl
// object
// 2 - virtual destructor allows us to destroy
// objects derived from FunctorImpl by invoking delete on a pointer to a 

//Now we define Functor. Functor follows a handle-body implementation
template<typename R, class TList>
class Functor
{    
    private:
    //Typedefinition for thebody time
    typedef FunctorImpl<R,TList> Impl;
    std::auto_ptr<Impl> spImpl; //auto_ptr deprecated but so far I prefer to follow the book  
    
    public:
    Functor();
    Functor(const Functor&); //Copy constructor
    Functor & operator=(const Functor&);//copy assignment operator
    //Functor & operator=(int i); //un overload cualquiera a assingment operator
    explicit Functor(std::auto_ptr<Impl>spImpl) ;   //extension constructor allows you to define classes derived from FunctorImpl and to initialize Functor
                                                  //directly with pointers to those classes
          
    // An explicit
    // destructor is not needed, because auto_ptr cleans up resources automatically.
};

// Why does the extension constructor take as its argument an auto_ptr and not a simple pointer?
// Constructing from auto_ptr is a clear statement to the outside world that Functor takes ownership of
// the FunctorImpl object. Users of Functor will actually have to type auto_ptr whenever they invoke
// this constructor; we assume that if they type auto_ptr , they know what auto_ptr is about

int main(){

}
