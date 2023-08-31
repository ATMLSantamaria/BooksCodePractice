//In some cases you need to strip a class from const

//E.g. smart_ptr<const T> . Internally you need to store the pointer to T and hold it internally. So you need to obtain T from const T


//Is easy to see how this template take the argument U or const U and in both cases give us a result that is a typedef to U (without const)
template <typename T>
class TypeTraits{
    private:
 
    template<class U> 
    struct UnConst
    {
        typedef U Result;
        enum { isConst = 0 };
    };
    template<class U> 
    struct  UnConst<const U>
    {
        typedef U result;
        enum { isConst = 1 };
    };
    
    public:

    typedef typename UnConst<T>::result NonConstType;
    
    
};

template<class Try>
void DoSomething(Try arg){

    typename TypeTraits<Try>::NonConstType arg_no_const;

    Try arg_internal;
    //We can not operate with a objetc of type Try because Try comes as const
    //arg_internal.SetMember(arg.GetMember()); -> Angry Compiler

    //But with a object of type Try but stripping the const we can operate
    arg_no_const.SetMember(arg.GetMember());
    

}

class TryImplemented{
    public:
    TryImplemented():member_(0){}
    int member_;
    void SetMember(int arg){member_=arg;}
    int GetMember() const {return member_;}
};

int main(){

    TryImplemented a;

    DoSomething<const TryImplemented>(a);

}