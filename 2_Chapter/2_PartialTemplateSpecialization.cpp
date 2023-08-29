// Partial template specialization allows you to specialize a class template for subsets of that template's
// possible instantiations set.


//1 - Example of total Specialization
template <class Window,class Controller>
class Widget{
    //Generic Implementation
};

// 2-Total Explicit specialization as follows
class ModalDialog{};
class MyController{};

// Important to remember, for a explicit specialization, the template class HAVE to exist already.
// The following code will not compile without the Widget class above

template<>
class Widget<ModalDialog,MyController>{
    //Specialised Implementation
};

// 3- Partial Explicit specialization. We want the specialization for any Window, and MyController
template<class Window>
class Widget<Window,MyController>{
    //Partially specialized implementation
};

//4 - Further Specialization of a specialize class.
// We can have a class Button that accept one parameter. We have the partial specialization before for any Window and My controler as above.


template<class Parameter>
class Button{};

class ButtonArgument_1{};
// We can further partial specialization for Button class that accept a template parameter
template<class ButtonArg>
class Widget<Button<ButtonArg>,MyController>{
    //Further partial specialization
};

//LIMITATION: Partial specialization does not work with Member Functions

//This feautre will be used extensively in chapter 3


int main(){

}

