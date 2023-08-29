template <int i>
struct Int2Type {
    enum {value=i};
};

//If we need to dispatch at runtime, a simple if-else is suffient

//However, what if we need to dispatch at compilation time?

//An if-else statement requires both branches to compile

//But if the condition would only be known in runtime



/* 
To duplicate an object contained in
NiftyContainer , you want to call either its copy constructor (for nonpolymorphic types) or a Clone()
virtual function (for polymorphic types). You get this information from the user in the form of a Boolean
template parameter 
*/
template <class T>
class NiftyContainer{
    //Class that contains pointer to objects of type T
    public:
    NiftyContainer(){}
    void DoSomething(){
        T * pSomeObj=nullptr;
        if (isPolimorphic_){
            T* pNewObj = pSomeObj->Clone();
            //Polimorphic algorithm
        } else {
            T* pNewObj = new T(*pSomeObj);
        }

    }

    void SetIsPolimorphic(bool isPolimorphic){isPolimorphic_=isPolimorphic;}
    bool isPolimorphic_;
    
    T * ptr1;
    T * ptr2;
};

template <class T,bool isPolimorphic>
class MoreNiftyContainer{
    public:
    MoreNiftyContainer(){}
    //In this case, since Int2Type with true and false is a different type, we can use a simple overloading that is resolve at compile time
    private:
    void DoSomething(T * pObj,Int2Type<true>){
        T* pNewObj = pObj->Clone();
    }
    void DoSomething(T * pObj,Int2Type<false>){
        T* pNewObj = new T(*pObj);
    }
    public:
    void DoSomething(T * pObj){
        DoSomething(pObj, Int2Type<isPolimorphic>());
    }

};

class Prueba{
    public:
    Prueba(){a=8;}
    int a;
};

int main(){
    NiftyContainer <Prueba> bb;
    bb.SetIsPolimorphic(false);
    //bb.DoSomething();
    //The compiler fails, even when the if-else go to the branch that does not require Clone
    
    //But in the MoreNiftyContainer, that is resolve in compile time I can use a Class without clone, just using the non polimorphic
    
    MoreNiftyContainer<Prueba,false> a;
    Prueba * aa= new Prueba();
    a.DoSomething(aa);

    //Of course, trying to use polimorphic with Prueba (that doesnt implement Clone) will create a compile error
    // MoreNiftyContainer<Prueba,true> c;
    // Prueba * cc= new Prueba();
    // c.DoSomething(cc);

}

