//This mechanism to detect if a type is a pointer relies in template specialization

class NullType{};

template <typename T>
class TypeTraits{
    private:
    template<class U>
    struct PointerTraits
    {
        enum{result=false};
        typedef NullType PointeeType; //Remember NullType is a placeholder type just to say "doesnt apply"
    };
    template<class U>
    struct PointerTraits<U*>
    {
        enum{result=true};
        typedef U PointeeType;
    };
    //In a similat way we can implement a ReferenceTrait
    template<class U>
    struct ReferenceTraits
    {
        enum{result=false};
        typedef NullType ReferredType;
    };
    template <class U>
    struct ReferenceTraits<U&>
    {
        enum{result=true};
        typedef U ReferredType;
    };

    //Also we can detect if there is a pointer to a member. However we will explore this topic later
    template <class U> struct PToMTraits
    {
        enum { result = false };
    };
    
    template <class U, class V>
    struct PToMTraits<U V::*>
    {
        enum { result = true };
    };


    public:
    enum{isPointer=PointerTraits<T>::result};
    typedef typename PointerTraits<T>::PointeeType PointeeType;

    enum{isReference=ReferenceTraits<T>::result};
    typedef typename ReferenceTraits<T>::ReferredType ReferredTypex;

    enum { isMemberPointer = PToMTraits<T>::result };
    
};
#include <vector>
#include <iostream>

class A{
    static int* a;
};

int main(){
    //We can check this mechanism using iterators of the std library
    
    const bool iterIsPtr = TypeTraits<std::vector<int>::iterator>::isPointer;

    std::cout << "vector<int>::iterator is ";
    std::cout << (iterIsPtr ? "fast" : "smart") << std::endl; 

    
    const bool isPtr = TypeTraits<int>::isPointer;
    std::cout << "int is ";
    std::cout << (isPtr ? "ptr" : "no ptr") << std::endl;

    const bool isPtr2 = TypeTraits<int *>::isPointer;
    std::cout << "int* is ";
    std::cout << (isPtr2 ? "ptr" : "no ptr") << std::endl;

    typedef NullType* Something;
    const bool isPtr3 = TypeTraits<int *>::isPointer;
    std::cout << "Something is ";
    std::cout << (isPtr3 ? "ptr" : "no ptr") << std::endl;

}