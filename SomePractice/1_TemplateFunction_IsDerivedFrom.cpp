#include <cassert>

//Implement a template function that determines if one class Children is derived from one class Parent

//The trick is done with the signature of a function, checking if a Children Pointer is convertible to a Parent Pointer

//Helper Class
template<class Parent, class Child>
class IsDerived {

  //First auxiliary classes for returning different sizes
  class No {};
  class Yes {No no[3];}; //Yes has different size than No

  //Now the function
  static Yes Test(Parent*); //Will be called if a Parent * is passed (or a pointer that is possible to convert to parent automatically)
  static No Test(...); //Catch other cases

  public:
  enum {Is = sizeof(Yes) == sizeof(Test(static_cast<Child*>(0))) };
};

template<class Parent, class Child>
bool IsDerivedFrom() {
  return IsDerived<Parent,Child>::Is;
}

class A {};

class B : public A {};

class M {};

//Template Function
int main() {
  bool test = false;
  test = IsDerivedFrom<A,B>();

  assert(test == true);

  bool test_false = true;
  test_false = IsDerivedFrom<A,M>();
  
  assert(test_false == false);
}



