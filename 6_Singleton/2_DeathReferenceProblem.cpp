//Adresss the dead reference issue when several singletons interact
#include <stdexcept>
class Singleton
{
    public:
    Singleton * Instance()
    {
        if (!pInstance_)
        {
            //Check for dead reference
            if (destroyed_)
            {
                OnDeadReference(); //One function, one responsibility. This responsibility -> ErrorHandling
            } else
            {
                Create(); //One function, one responsibility. This responsibility -> Create the instance
            }
        }
        return pInstance_;
    }

    static void Create()
    {
        //Initialize pInstance
        static Singleton onlyInstance_;
        pInstance_=&onlyInstance_;
    }

    static void OnDeadReference()
    {
        throw std::runtime_error("Dead Reference Detected\n");
    }
    virtual ~Singleton()
    {
        pInstance_=NULL;
        destroyed_=true;
    }

    static Singleton * pInstance_;
    bool destroyed_;
};

int main(){

    // Singleton* Singleton::pInstance_ = 0;
    // bool Singleton::destroyed_ = false;



}
