#include "../LokiIncludes.h"

// Sometimes you might need to generate a small structure with unnamed fields, known in some languages
// (such as ML) as a tuple.

// What are tuples?
template<class T>
struct Holder
{
    T value_;
};

typedef Loki::GenScatterHierarchy<LOKI_TYPELIST_3(int,int,int),Holder> Point3D;

// Working with Point3D is a bit clumsy, because you have to write .value_ after any field access
// function.

//Remember
Point3D obj;

int x = Loki::Field<0>(obj).value_;

// What we need here is to generate a structure the same way GenScatterHierarchy does, but
// with the Field access functions returning references to the value_ members directly. That is,
// Field<n> should not return a Holder<int>& , but an int& instead.

// Loki defines a Tuple template class that is implemented similarly to GenScatterHierarchy but that
// provides direct field access.
typedef Loki::Tuple<LOKI_TYPELIST_3(int,int,int)> Point3D_2;
Point3D_2 obj2;

int y = Loki::Field<0>(obj2);

int main(){}