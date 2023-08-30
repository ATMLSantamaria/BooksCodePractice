//As stated earlier -> Partial specialization for template functions does not exist.

//What if we need to use a similar functionality, like next:

template<class T,class U>
T * Create(const U& arg){
    return new T(arg);
}

//This function create a new object, passing an argument to the constructor

//Now arise the situation.

/* 
WE have object of type Widget, that are untouchable legacy code and MUST take 2 arguments in its constructor. The second being a fixed parameter like -1
My newer classes, derived from Widget, only need one parameter.
*/

//How can you specialize Create so that it treats Widget differently from all other types?

// 1- Create a function CreateWidget -> Then you dont have a uniform interface for Widget and its derive classes. This would make Create unusable in generic code.

// 2 - You cannot partially specialise a function. So you cannot create a particular case for Widget-> the next is illegal

/* 
template<class U>
Widget * Create<Widget,U>(const U& arg){
    return new Widget(arg, -1)
} 
 */

//Only remaining posibility is OVERLOADING. And here we have 2 options.

// 1 - For the case of newer classes, pass a Dummy object of type T to the argument of create. And for the legacy pass a dummy object of type Widget.
template<class T,class U>
T * Create(const U& arg, T dummy){
    return new T(arg); //T is dummy. Not used at all
}
//Widget is the legacy class that requiers a int as a second argument for the constructor
class Widget{
    public:
    template<class T>
    Widget(T arg1, int arg2){};
};
template<class U>
Widget * Create(const U& arg, Widget dummy){
    return new Widget(arg,-1); //Widget is passed but not used, since we only need to pass one argument
}
//This solution implies the creation of dummy classes that could eventually be big (if Widget or T are big classes it could be heavy)

// The optimal solution.
// 2 - WE use a light weight vehicle to transport information about T to Create. And then to use overloading
// The Type2Type allows us to do this. It is a type's representative, a light identifier that you can pass to overloaded functions.
template <class T>
struct Type2Type
{
    typedef T OriginalType;
};
//Typedef is devoid of any value, but distinct types in T leads to different Type2Type instantiations.
//So it is possible to use this type's representative lightweight identifier to overload functions
template<class T,class U>
T * Create(const U& arg,Type2Type<T>){
    return new T(arg);
}
template<class U>
Widget * Create(const U & arg,Type2Type<Widget>){
    return new Widget(arg,-1);
}
//As we can see in main the second argument serves only to choose the appropiate overload.
//Now is possible to specialise Create for various instantiations of TypeToType, which can be mapped to various types in the application 


#include <string>
int main() {
    //Use create
    std::string * ptr_string = Create("Hello",Type2Type<std::string>());
    Widget * ptr_widget = Create(100,Type2Type<Widget>()); 

}