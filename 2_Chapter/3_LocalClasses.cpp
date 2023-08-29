// We will create a class Interface and a template function that helps to adapt this interface to others

class Interface{
    public:
    virtual void Fun()=0;
    //Other stuff
};

//Local classes define inside a template function can use the classes passed as parameters
template<class T,class P>
Interface * MakeAdapter(const T & obj, const P & arg){

    class Local : public Interface{
        public:
        Local(const T & obj,const P & arg):obj_(obj),arg_(arg){}

        virtual void Fun(){
            obj_.Call(arg_);
        }

        private:
        T obj_;
        P arg_;
    };


    return new Local(obj,arg);

}
//Classes in the application code
#include <string>
#include <iostream>
class P {
    public:
    P(){
         name_ = "My name is P\n";
    }
    std::string GetName(){
        return name_;
    }
    private:
    std::string name_;
};

class P2 {
    public:
    P2(){
         name_ = "My name is P2\n";
    }
    std::string GetName(){
        return name_;
    }
    private:
    std::string name_;
};

template<class P>
class T{
    public:
    T(){}
    void Call(P arg){
        std::cout << arg.GetName() << std::endl;
    }
};

int main(){
    Interface * ptr;

    T<P> object;
    P argument;
   
    ptr = MakeAdapter<T<P>,P>(object,argument);
    ptr->Fun();
    
    delete ptr;
    ptr = nullptr;

    T<P2> object2;
    P2 argument2;

    ptr = MakeAdapter<T<P2>,P2>(object2,argument2);
    ptr->Fun();
    delete ptr;
    ptr = nullptr;


}