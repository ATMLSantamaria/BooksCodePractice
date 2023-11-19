#include <cassert>

//Points to remember. Partial Specialization Syntax. Members that we can return in compile time should be static, and for be static they have to be const
// To be able to access a member like A::Result that member has to be static


//Template
template<typename C,typename T>
class IsSame {
 public:
 static const bool Result = false;
};


//Template partial specialization
template<typename C>
class IsSame<C,C> {
 public:
 static const bool Result = true;
};


//Template Function
template<typename C,typename T>
bool IsSameClass() {
  return IsSame<C,T>::Result;
}


class A{};
class B{};


int main() {
  bool a = IsSameClass<A,A>();
  assert(a);
  bool b = IsSameClass<A,B>();
  assert(b == false);

}



