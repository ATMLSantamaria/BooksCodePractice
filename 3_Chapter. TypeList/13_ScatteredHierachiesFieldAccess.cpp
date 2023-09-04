// #include "../loki-0.1.7/include/loki/TypeTraits.h"
// #include "../loki-0.1.7/include/loki/TypeManip.h"
// #include "../loki-0.1.7/include/loki/Typelist.h"
// #include "../loki-0.1.7/include/loki/NullType.h"
// #include "../loki-0.1.7/include/loki/Tuple.h"
// #include "../loki-0.1.7/include/loki/TypelistMacros.h"
// #include "../loki-0.1.7/include/loki/HierarchyGenerators.h"
#include "../LokiIncludes.h"
// #include "../loki-0.1.7/include/loki/"
#include <string>

#define TypeList Typelist

using namespace Loki;

class Widget{};


template <class T>
struct Holder
{
T value_;
};

typedef GenScatterHierarchy<LOKI_TYPELIST_4(int, int, std::string, Widget),Holder>
WidgetInfo;

WidgetInfo obj;

int x = Field<0>(obj).value_; // first int
int y = Field<1>(obj).value_; // second int

int main(){}