// In C++ a bald pointer to a polymorphic type does not strictly have first-class
// semantics because of the ownership issue

// To lift the burden of lifetime management from Functor 's
// clients, it's best to provide Functor with value semantics (well-defined copying and assignment).
// Functor does have a polymorphic implementation, but that's hidden inside it. We name the
// implementation base class FunctorImpl .

//Note: The Command::Execute() of the Command pattern become in C++ the operator()

class Functor_1{
    public:
    void operator()(); //What if we want to return other types
    //...
};

//Nota in the template parameter typename and class are absolutly the same (in other context no)
template<typename ResultType>
class Functor_2{
    public:
    ResultType operator()();
};
//We dont have Functor, but a family of Functor, since a Functor<std::string> is different than a Functor that return string is different than one that return an int
//Second issue, we want the Functor operatoer() to accept parameters arguments.

//Maybe is needed to pass some info that was not available at construction time.

//Template variable parameter does not exist. -> Set a number of maximum possible parameters

//Template with same name and different parameter number also are not allowed

// template<typename ResultType>
// class Functor
// {};
// template<typename ResultType,class Param1>
// class Functor
// {};

//Invalid code

// Solution -> TypeList
#include "../LokiIncludes.h" //Includes from LokiLibrary

//We can use a TypeList for passing the "variable" parameters and combine it with the "partial specialization" until we have Functor accepting
//from 0 to 15 arguments in its operator()

template<typename ResultType,class TList>
class Functor 
{

};

//This would be a possible call
Functor<double,LOKI_TYPELIST_2(int,double)> myFunctor;

//However, even if TypeList help us with the now pseudo variable parameter list we still need to write repetitive code within each partial specialisation


int main(){

}

