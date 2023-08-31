//This 2 types can be use to mark border cases in type calculations

class NullType{};

//This class serves as a null marker for types

//Use in cases where a type must be there syntactically but does not have a semantic sense
//Or in the typelist faciltiy we will do NullType marks the end of the typelist


//Second helper is EmptyType
struct EmptyType{};
//Legal Type to inherit from
//You can pass  values of this type
//Useful to be used as a "default" type for a template


class A :public EmptyType{};
int main(){
    EmptyType * empty  = new EmptyType();
    A * a = new A();
    empty = a;


}