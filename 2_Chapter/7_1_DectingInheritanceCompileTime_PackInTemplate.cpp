//Implement all the ideas of the file 7 but packed in a template

template<class T, class U>
class Conversion{
    typedef char Small;
    class Big{char dummy[2];};

    //Overload functions to return different types in function of the possibility of conversion of T into U
    static Small Test(U);
    static Big Test(...);

    //Function necessary to use T in case its constructor is private
    static T MakeT();

    public:
    enum{exists=
         sizeof( Test(MakeT())) == sizeof(Small) };

    enum { sameType = false };
};

//We implement a partial specialization of Conversion
template<class T>
class Conversion<T,T>{
    public:
    enum{exists=1,sameType=1};
};

//Now we have the general class to check the conversion, and also the partial specialisation for the case where the 2 types are identical
//Now is very easy to determine inheritance
#define SUPERSUBCLASS(T,U) \
    (Conversion<const U* ,const T* >::exists && \
    !Conversion<const T* ,void *>::sameType) 

//Macro will work with pointers or with the direct classes, but with the void check the pointer is necessary

//SUPERSUBCLASS does its job by evaluating the convertibility from a const U* to a const
//T* . There are only three cases in which const U* converts implicitly to const T* :
//1 - T is the same type as U .
//2 - T is an unambiguous public base of U
//3 - T is void .

//IF a stricter code, tha pass only if T is super class of U, and not if they are the same class, it is needed. The next will work
#define SUPERSUBCLASS_STRICT(T,U) \
    (SUPERSUBCLASS(T,U) && \
    !Conversion<const U ,const T >::sameType)

#include <iostream>
#include <vector>
class Proof{};
class ChildrenOfProof: public Proof{};
class NotRelated{};

int main(){
    std::cout 
                << Conversion<double,int>::exists << " "
                << Conversion<char,char*>::exists << " "
                << Conversion<double,double>::exists << " "
                << Conversion<std::vector<int>,std::vector<int>>::exists << " "
                << Conversion<std::vector<double>,std::vector<int>>::exists <<
                std::endl;

    std::cout << "with macro\n";

    if(SUPERSUBCLASS(Proof,ChildrenOfProof)){
        std::cout << "IS a child or same class" << std::endl;
    } else {
        std::cout << "IS NOT a child" << std::endl;
    }

    if(SUPERSUBCLASS(Proof,NotRelated)){
        std::cout << "IS a child or same class" << std::endl;
    } else {
        std::cout << "IS NOT a child" << std::endl;
    }

    if(SUPERSUBCLASS(Proof,Proof)){
        std::cout << "IS a child or same class" << std::endl;
    } else {
        std::cout << "IS NOT a child" << std::endl;
    }

    if(SUPERSUBCLASS_STRICT(Proof,Proof)){
        std::cout << "IS a child" << std::endl;
    } else {
        std::cout << "IS NOT a child" << std::endl;
    }

            
}