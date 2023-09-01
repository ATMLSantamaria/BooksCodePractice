//Typelist are a C++ tool for manipulating collections of types. They offer for types all the fundamental operations that list of values support

 

//There are design patterns that specify and manipulate collection of types (e.g. Abstract Factory and Visitor).

 

//Using traditional (not template metaprogramming ) coding techniques you can manipulate collections of tpes by repetition.

//This create some code bloating, and normally we though that there is not a possibility of get better than this.

//But, typelist let you automate task that you usually confine to your editor macro capability. Typelist bring power to C++

 

//The purpose here is:

// 1 - Understanding the typelist concept

// 2 - Understand how typelist can be created and processed

// 3 - Be able to manipulate typelist effectively

// 4 - Know the main uses of typelist and the programming idioms they enable and support

 

//Need for TypeList

 

//Sometimes you must repeat the same code for a number of types and templates cannot be of help. For example implementing an Abstract Factory

class Window{};

class Button{};

class ScrollBar{};  

class WidgetFactory

{

    public:

        virtual Window* CreateWindow()=0;

        virtual Button* CreateButton()=0;

        virtual ScrollBar* CreateScrollBar()=0;

};

 

//If you want to generalize this concept and put it into a library you need to pake possible for the user to create factories of arbitrary colelction of types,

//not just the fixed Window, Butto and ScrollBar

//Templates dont support this feature out of the bow

template<class T, class U>

struct Typelist{

    typedef T Head;

    typedef U Tail;

};

//TypeList of 3 or more elements (holding 3 types of char)

typedef Typelist<char, Typelist<signed char, unsigned char> > CharList;

 

//Typelist of 0

class NullType {};

//Typelist of 1

typedef Typelist<int, NullType> OneTypeOnly;

//Typelist of 3 vhar variants with Nulltype as termination maker

typedef Typelist<char, Typelist<signed char,Typelist<unsigned char, NullType> > > AllCharTypes;

int main(){

 

}  