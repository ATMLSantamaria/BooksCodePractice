
// primitive static variables with compile time constant
// In this case, x is initialized before any code in the program is executed, most likely at load time
static int a=100;

// Another slight improvement is to have Instance return a reference instead of a pointer. The problem
// with having Instance return a pointer is that callers might be tempted to
class Singleton
{
    public:
    static Singleton * Instance()
    {
        // The simplest solution for destroying the singleton is to rely on language mechanisms. For example, the
        // following code shows a different approach to implementing a singleton. Instead of using dynamic
        // and a static pointer, the Instance function relies on a local static variable.
        if(!pInstance_){
            return new Singleton();
        }

    }
    private:
    Singleton(){} //Constructor private to avoid undesired copies
    Singleton(const Singleton &){} //In last c++ is possible to specificaly delete 
    Singleton & operator=(const Singleton&){}  //In last c++ is possible to specificaly delete 
    // public:
    //~Singleton(){} //Destructor private to avoid the user thinking that he should call it
    static Singleton * pInstance_;

};
Singleton * Singleton::pInstance_ = 0;
int main()
{
    Singleton * singleton = Singleton::Instance();
}