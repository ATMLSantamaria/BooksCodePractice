// A policy defines a class interface or a class template interface
//2 Policy Classes (implementations of Creator Policy)
#include <memory>
template <class T>
struct OpNewCreator
{
static T* Create()
{
return new T;
}
};
template <class T>
struct MallocCreator
{
static T* Create()
{
void* buf = std::malloc(sizeof(T));
if (!buf) return 0;
return new(buf) T;
}
};

//Host class->Notice the power here, you are defining in the template from whom WidgetManager will inherit
template <class CreationPolicy>
class WidgetManagerSimple : public CreationPolicy
{
    
};
class Widget{};
// When instantiating the WidgetManager template the client passes the desired policy:
// Opcion 1 -> Policy of using new
// Option 2 -> Policy of using malloc
typedef WidgetManagerSimple< OpNewCreator<Widget>> MyWidgetMgr_withPolicy1;
typedef WidgetManagerSimple< MallocCreator<Widget>> MyWidgetMgr_withPolicy2;

// Often, as is the case above, the policy's template argument is redundant. It is awkward that the user must
// pass OpNewCreator 's template argument explicitly. Typically, the host class already knows, or can easily
// deduce, the template argument of the policy class. In the example above, WidgetManager always
// manages objects of type Widget , so requiring the user to specify Widget again in the instantiation of
// OpNewCreator is redundant and potentially dangerous.

// For that we have:
// Implementing Policy Classes with Template Template Parameters

template<template<class Created> class CreationPolicy>
class WidgetManager : public CreationPolicy<Widget>
{

};
//IMPORTANT
// the Created symbol does not contribute to the definition of WidgetManager .
// You cannot use Created inside WidgetManager —it is a formal argument for CreationPolicy (not
// WidgetManager ) and simply can be omitted.

//Now application code only need to provide the name of the policy
typedef WidgetManager<OpNewCreator> MyWidgetManager;

int main(){

}