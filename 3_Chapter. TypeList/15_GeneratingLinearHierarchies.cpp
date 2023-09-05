#include "../LokiIncludes.h"

template <class T>
class EventHandler{
    public:
    virtual void OnEvent(const T&,int eventId)=0;
    virtual ~EventHandler(){}
};

// We can use GenScatterHierarchy to distribute EventHandler to each type in a typelist:

class Window{};class Button{};class ScrollBar{};
typedef Loki::GenScatterHierarchy<LOKI_TYPELIST_3(Window,Button,ScrollBar),EventHandler> WidgetEventHandler;


// The disadvantage of GenScatterHierarchy is that it uses multiple inheritance. If you care about
// optimizing size, GenScatterHierarchy might be inconvenient, because Widget-EventHandler
// contains three pointers to virtual tables, [4] one for each EventHandler instantiation


// sizeof(EventHandler) is 4 bytes, then sizeof(WidgetEventHandler) will likely be 12 bytes,
// and it grows as you add types to the typelist. The most space-efficient configuration is to have all virtual
// functions declared right inside WidgetEventHandler , but this dismisses any code generation
// opportunities


// A nice configuration that decomposes WidgetEventHandler into one class per virtual function is a
// linear inheritance hierarchy

// How can we provide a mechanism that automatically generates a hierarchy like this? A recursive template
// similar to GenScatterHierarchy can be of help here. There is a difference, though. The user-provided
// class template must now accept two template parameters. One of them is the current type in the typelist, as
// in GenScatterHierarchy . The other one is the base from which the instantiation derives.



//Remember the ScatteredHierarchy to compare
template <class TList, template <class> class Unit>
class GenScatterHierarchy2;

//GenLinearHierarchy
template<class TList,template<class AtomicType,class Base> class Unit,class Root=Loki::EmptyType> //We give a defailt value to Root and an additional parameter to Unit
class GenLinearHierarchy2;

//Partial Specialization
template<class T1,class T2,template<class,class> class Unit,class Root>
class GenLinearHierarchy2<Loki::Typelist<T1,T2>,Unit,Root> : public Unit<T1, Loki::GenLinearHierarchy<T2,Unit,Root> >
{
};
template<class T,template<class,class> class Unit,class Root>
class GenLinearHierarchy2<LOKI_TYPELIST_1(T),Unit,Root> : public Unit <T,Root>
{
};

template<class T,class Base>
class EventHandler2 : public Base
{
    public:
    virtual void OnEvent(T& obj, int eventId) = 0;
    virtual ~EventHandler2();
};

// GenScatterHierarchy and GenLinearHierarchy work great in tandem. In most cases, you would
// generate an interface with GenScatterHierarchy and implement it with GenLinearHierarchy .

typedef GenLinearHierarchy2<LOKI_TYPELIST_3(Window,Button,ScrollBar),EventHandler2> MyEventHAndler;
int main(){}
