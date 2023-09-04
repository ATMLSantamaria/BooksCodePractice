#include <vector>


class A{};class B{};
//T cant be used as a parameter-> it just mean that some class will match TemplateType<A>
template<template<class T> class TemplateType>
class Prueba : public TemplateType<A>{
    
};

//Thats why T can be easily omitted
template<template<class> class TemplateType>
class Prueba2 : public TemplateType<A>
{
    //The power is obvious. You can create other instances of TemplateType inside with other parameters
    TemplateType<B> b;

};

int main(){

}