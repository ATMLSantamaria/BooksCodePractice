#include "TypeListFeatures.h"
// Typelist objects have no use as they are; they are devoid of any runtime state or functionality. An
// important need in programming with typelists is to generate classes from typelists. Application
// programmers sometimes need to fill a class with code—be it virtual function signatures, data declarations,
// or function implementations—in ways directed by a typelist. We will try to automate such processes with
// typelists.

//Utility->build classes by applying each type in a typelist to a basic template, provided by the user. This way, the clumsy process of distributing types in the
// typelist to user code is encapsulated in the library; the user need only define a simple template of one
// parameter.

//This mechanism is called GenScatterHierarchy;

template <class TList,template<class> class Unit>
class GenScatterHierarchy;

// GenScatterHierarchy specialization: Typelist to Unit. ATTENTION, a template class can inherit of the same template class
//with other parameters becasue template class with different parameters are actually different types
template<class T1,class T2,template<class> class Unit>
class GenScatterHierarchy<TypeList<T1,T2>,Unit> : public GenScatterHierarchy<T1,Unit>,public GenScatterHierarchy<T2,Unit>
{
    public:
    typedef TypeList<T1,T2> TList;
    typedef GenScatterHierarchy<T1,Unit> LeftBase;
    typedef GenScatterHierarchy<T2,Unit> RightBase;
};

//Specialisation for an atomic type (non typeList) being passed to Unit
template<class AtomicType,template<class> class Unit>
class GenScatterHierarchy : public Unit<AtomicType>
{
    typedef Unit<AtomicType> LeftBase;
};
//Do Nothing for NullType
template<template<class> class Unit>
class GenScatterHierarchy<NullType,Unit>
{
};

//What does GenScatterHierarchy do?
// Ultimately, an instantiation of GenScatterHierarchy ends up inheriting Unit instantiated with every
// type in the typelist. For instance, consider this code

//E.G.
template<class T>
struct Holder
{
    T value_;
};

#include <string>
class Widget{};
//Instantiation of GenScatterHierarchy. Notice how holder is a template but when we pass to GenScatterHierarchy we dont need code its parameter
typedef GenScatterHierarchy<TYPELIST_3(int,std::string,Widget),Holder> WidgetInfo;

//What is WidgetInfo? -> GenScatterHierarchy generates class hierarchy for you by repeatedly instantiating a class
//template that you provide as a mode -> Then all that is collected in WidgetInfo.
//We call the class hierarchy in scattered, because the types in the typelist are scattered in distinct root classes

// As an effect of inheriting Holder<int> , Holder<string> , and Holder<Widget> , WidgetInfo
// has one member variable value_ for each type in the typelist

// As an effect of inheriting Holder<int> , Holder<string> , and Holder<Widget> , WidgetInfo
// has one member variable value_ (due to Holder) for each type in the typelist

//You can use WidgetInfo to access the string stored in a WidgetInfo object

WidgetInfo obj;
std::string name = (static_cast<Holder<std::string>&>(obj)).value_;
// The explicit cast is necessary to disambiguate the member variable name value_ . Otherwise, the compiler
// is confused as to which value_ member you are referring to.

#include <iostream>
int main(){
    std::cout << name << std::endl;
}
