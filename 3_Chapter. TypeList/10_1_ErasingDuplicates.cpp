#include "TypeListFeatures.h"
//An important operation on typelists is to erase duplicate values.

//Transfor a TypeList with repeated values into one without the repeated values
class Widget{};class Button{};class TextField{};class ScrollBar{};
typedef TYPELIST_6(Widget, Button, Widget, TextField, ScrollBar, Button) RandomList;
typedef TYPELIST_6(int,double,int,float,char,double) ElementalTypesList;

//Into a TypeList like this
typedef TYPELIST_4(Widget, Button, TextField, ScrollBar) TransformedRandomList;
typedef TYPELIST_4(int, double, float, char) TransformedElementalTypesList;

//                        Algorithm
// NoDuplicates
// Input: Typelist TList
// Output: Inner type definition Result
// If TList is NullType , then Result is NullType .
// Else
// Apply NoDuplicates to TList::Tail , obtaining a temporary typelist L1 .
// Apply Erase to L1 and TList::Head . Obtain L2 as the result.
// Result is a typelist whose head is TList::Head and whose tail is L2 .
template<class TList>struct NoDuplicates;

//If TList is NullType, Result is NullType
template<>
struct NoDuplicates<NullType>
{
    typedef NullType Result;
};
template<class Head,class Tail>
struct NoDuplicates<TypeList<Head,Tail>>
{
    private:
    typedef typename NoDuplicates<Tail>::Result L1;
    typedef typename Erase<L1,Head>::Result L2;
    public:
    typedef TypeList<Head,L2> Result;
   
};



int main(){

}
