#include "TemplateHelperFeatures.h"
#include "TypeListFeatures.h"
#include <iostream>
//We want to order a List by inheritance relationship

//We have
class Widget{
    public:
    void Name(){std::cout << "Widget\n";}
};
class ScrollBar : public Widget{
    public:
    void Name(){std::cout << "ScrollBar\n";}
};
class ScrollBarInteractive : public ScrollBar{
    public:
    void Name(){std::cout << "ScrollBarInteractive\n";}
};
class Button : public Widget{
    public:
    void Name(){std::cout << "Button\n";}

};
class GraphicButton :public Button{
    public:
    void Name(){std::cout << "GraphicButton\n";}
};
class GraphicButtonInteractive :public GraphicButton{
    public:
    void Name(){std::cout << "GraphicButtonInteractive\n";}
};


//So Scroll Bar and Button are Siblings (and childs f Widget), while GraphicalButton is child of Button

//We have a TypeList like this

//TYPELIST_4(Widget, ScrollBar, Button, GraphicButton)

//We want to order like this

//TYPELIST_4(ScrollBar, GraphicButton, Button, Widget)

//With the most derived class in front and without altering the order of siblings

//To order we need a ordering function in compile time, and we alredy created to detect inheritance relationship SUPERSUBCLASS(T,U)

//NOTE
// We cannot use a full-fledged sorting algorithm here because we don't have a total ordering relationship; we
// don't have the equivalent of operator< for classes. Two sibling classes cannot be ordered by
// SUPERSUBCLASS(T, U) .

//Also we need the auxiliar algorithm MostDerived



//                         Algorithm
// MostDerived
// Input: Typelist TList , type T
// Output: Inner type definition Result
// If TList is NullType , the result is T .
// Else
// Apply MostDerived to TList::Tail and Base . Obtain Candidate .
// If TList::Head is derived from Candidate , the result is TList::Head .Else, the result is Candidate .

template<class TList,class T>
struct MostDerived;

template<class T>
struct MostDerived<NullType,T>
{
    typedef T Result;
};

template<class Head,class Tail,class T>
struct MostDerived<TypeList<Head,Tail>,T>
{
     private:
     typedef typename MostDerived<Tail,T>::Result Candidate;
     public:
     //Now we use the SUPERSUBCLASS macro and Select to know which one is derived of which one
     typedef typename Select<SUPERSUBCLASS(Candidate,Head),Head,Candidate>::Result Result;
};

//                       Algorithm
// DerivedToFront
// Input: Typelist TList
// Output: Inner type definition Result
// If TList is NullType , then Result is NullType .
// Else
// Find the most derived type from TList::Head in TList::Tail . Store it in a
// temporary variable TheMostDerived .
// Replace TheMostDerived in TList::Tail with TList::Head , obtaining L as the result.
// Build the result as a typelist having TheMostDerived as its head and L as its tail.

 

template<class TList>
struct DerivedToFront;

//If TList is NullType , then Result is NullType 
template<>
struct DerivedToFront<NullType>
{
    typedef NullType Result;
};
//else
template<class Head,class Tail>
struct DerivedToFront<TypeList<Head,Tail>>
{
    //find most derived
    private:
    typedef typename MostDerived<Tail,Head>::Result TheMostDerived;

    typedef typename Replace<Tail,TheMostDerived,Head>::Result Temp;
    typedef typename DerivedToFront<Temp>::Result L;
    public:
    typedef TypeList<TheMostDerived,L> Result;

};


//unordered TypeList
typedef TYPELIST_6(GraphicButtonInteractive,Widget, ScrollBar, Button, GraphicButton,ScrollBarInteractive) UnorderedTypeList;

typedef DerivedToFront<UnorderedTypeList>::Result OrderedTypeList;


int main(){

    TypeAt<OrderedTypeList,0>::Result variableA;
    TypeAt<OrderedTypeList,1>::Result variableB;
    TypeAt<OrderedTypeList,2>::Result variableC;
    TypeAt<OrderedTypeList,3>::Result variableD;
    TypeAt<OrderedTypeList,4>::Result variableE;
    TypeAt<OrderedTypeList,5>::Result variableF;

    //The order should be (ScrollBar, GraphicButton, Button, Widget)
    variableA.Name();variableB.Name();variableC.Name();variableD.Name();variableE.Name();variableF.Name();

}