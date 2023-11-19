#include <cassert>
#include <string>


// There is a class with a private member. This class is in a library (we can not modify its code). How to get access to that data member

class Something {
 public:
  Something() {
    topSecretValue = 54;
  }
  bool somePublicBool = true;
  int somePublicInt = 7; 
  std::string somePublicString;
 private:
  int topSecretValue;
};

//How to access topSecretValue?

// 1 - Create a class with exactly the same DATA members in the same order
// 2 - Give that class a public method that return the private variable
// 3 - Use reinterpret_cast to change a pointer to the original class into a pointer of the new class
// 4 - To use c style cast is also possible although unsafe


//This trick work in base of the way C++ has of store DATA members and Functions. Data members will be contiguous and their order not affected by functions of the class. Creating
// a simular class with more methods still allow us to cast the old class and assure a total correspondence of the data space, and therefore access to data members with the getter

class SomethingAccessible {
 public:
  int getTopSecretValue() {
    return topSecretValue;
  }
  std::string doSomething(){return "Hello\n";}
  void doSomethingMore(){}
  bool somePublicBool = true;
  int somePublicInt = 7;
  std::string somePublicString;
 private:
  int topSecretValue;
};

int main() {

    Something object;
    
    SomethingAccessible * pointer_to_something_accessible = reinterpret_cast<SomethingAccessible *>(&object);

    assert(54 == pointer_to_something_accessible->getTopSecretValue());

    
    SomethingAccessible * pointer_to_something_accessible_c_style = (SomethingAccessible *)(&object);
    
    assert(pointer_to_something_accessible_c_style->getTopSecretValue() == 54);
}
