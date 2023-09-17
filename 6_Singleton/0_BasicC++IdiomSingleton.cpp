//Typical C++ approach to build a singleton
#include <iostream>
#include <string>
//This, of course normally in the .h
class Singleton 
{
    public:
    static Singleton * instance()
    {
        if (!ptrInstance_)
        {
            return new Singleton();
        } else 
        {
            return ptrInstance_;
        }
    }
    void randomFunction(){
        std::cout << "Hello, I am" << name_ << "the only Singleton you will ever see here\n";
    }
    private:
    Singleton(){
        name_="MySingleton\n";
    }//Prevent any user for be able to instantiate a Singleton
    Singleton(const Singleton&){}//Prevent any user for being able to copy a Singleton

    //static Singleton instance_; //Bad option. This would mean dynamic initialization and the order of dynamic initialization is undefined. We can
    //try to use instance_ in other translation unit and it could be that the object does not exist yet
    static Singleton * ptrInstance_; //static initialization (it is a type without a constructor initialized with a compile-time constant).
    // The compiler performs static initialization before the very first assembly statement of the program gets
    // . (Usually, static initializers are right in the file containing the executable program, so loading is
    // initializing.) On the other hand, C++ does not define the order of initialization for dynamically initialized
    // objects found in different translation units, which is a major source of trouble.
    std::string name_;
};

Singleton * Singleton::ptrInstance_ = 0;

//In this file all the dangers of C++ are ilustrated
//Without the variable name_ in the singleton you could use a Singleton * ptr pointing to nullptr and just use randomFunction even if the pointer point to 
//memory 0x0. Without name the randomFunction will be executed and print something. 
//Also you can delete the handler and still use 
//This is something I need to investigate more

int main()
{
    Singleton * handler = nullptr;
    int a = 0;
    a++;
    std::cout << a << std::endl;

    handler = Singleton::instance();

    handler->randomFunction();

    Singleton * handler2;
    //handler2->randomFunction();//Even using it unitialised point to the correct place. However you cant use handler2 to delete singleton
    
    //delete handler2; //Error

    //delete handler;

    std::cout << "Now you ""cant"" use Singleton\n";

    handler->randomFunction();
    std::cout << "But in  reality you can use it as long as you it does not contain any variable that is non static\n";
}



