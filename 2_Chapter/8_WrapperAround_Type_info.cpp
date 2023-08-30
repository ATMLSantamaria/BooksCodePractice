//std::type_info class provides the ability to investigate objects at runtime

//typeid operator return a reference to typeinfo

//type_info provide a operator== and operator!= to compare if both ptr results point to same kind of objects, also name and before members to give extra info
#include <typeinfo>
#include <cassert>
class Base{
    public:
    Base():b(6){}
    double b;
};
class Derived:public Base{
    public:
    Derived():Base(){
        a=2;
    }
    int a;
};

#include <iostream>
void Fun(Base * pObj){
    if(typeid(pObj)==typeid(Derived)){
        //pObj actually points to a Derived object
        std::cout << "pobj point to Derived\n";
    }
}

//Limitation, you cannot store type_info Objects, its copy constructor and assignment operator are disabled
//You could store pointers to type_info Objects but then you could only compare them with type_info::operator==
//To index a group of pointers to type_info you could only use type_info::before

//This is a motivation to create a Wrapper class around type_info that:
//1 - Stores a Pointer to a type_info Object and provides:
//2 - All member functions of type_info
//3 - Value Semantics -> Copy Constructor and assignment operator
//4 - Seamless (impecables) Comparations defined by < and > 

//NOTA: Objetos type_info se guardan en static storage, no desaparecen cuando el scope donde se han creado se acaba

class TypeInfo{
    public:
    //Constructor
    TypeInfo();//needed for containers
    TypeInfo(const std::type_info&); //constructor of conversion from std::type_info
    TypeInfo(const TypeInfo &);//Copy Constructor
    TypeInfo & operator=(const TypeInfo &);//Assignment operator
    //Functions needed for compatibility (they are present in std::type_info)
    bool before(const TypeInfo&) const; //This is a comparison function (for example needed to create a map)
    const char * name() const;
    // Access for the wrapped std::type_info
    const std::type_info& Get() const;

    private:
    const std::type_info * pInfo_;
};

//Implementation
inline TypeInfo::TypeInfo(){
    class Nil{};
    pInfo_ = &typeid(Nil);
    assert(pInfo_);
}

inline TypeInfo::TypeInfo(const std::type_info& ti):pInfo_(&ti){
    assert(pInfo_);
}

inline TypeInfo::TypeInfo(const TypeInfo& other){
    assert(other.pInfo_);
    //Deep copy does not make sense in this case, anyway you cant copy the underlying std::type_info. So with this copy of TypeInfo, you have 2 wrappers
    //pointing to the same std::type_info object
    pInfo_=other.pInfo_;
}

inline TypeInfo & TypeInfo::operator=(const TypeInfo& other){
    assert(other.pInfo_);
    //Deep copy does not make sense in this case, anyway you cant copy the underlying std::type_info. So with this copy of TypeInfo, you have 2 wrappers
    //pointing to the same std::type_info object
    pInfo_=other.pInfo_;
}

inline bool TypeInfo::before(const TypeInfo& other) const {
    assert(pInfo_);
    return pInfo_->before(*other.pInfo_);
}

inline const std::type_info & TypeInfo::Get() const {
    assert(pInfo_);
    return *pInfo_;
}

inline const char* TypeInfo::name() const
{
    assert(pInfo_);
    return pInfo_->name();
}

inline bool operator==(const TypeInfo& left_hs, const TypeInfo& right_hs)
{ return left_hs.Get() == right_hs.Get(); }

inline bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
{ return lhs.before(rhs); }

inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
{ return !(lhs == rhs); }    

inline bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
{ return rhs < lhs; }

inline bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
{ return !(lhs > rhs); }
    
inline bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
{ return !(lhs < rhs); }

///

void Fun2(Base* pObj)
{
    TypeInfo info = typeid(Derived);

    if (typeid(*pObj) == info){
    //... pBase actually points to a Derived object ...
        std::cout << "pBAse points to derived\n"; 
    }

}

int main() {
    Base a;
    Base * ptr =&a;

    ptr= new Derived();

    Fun2(ptr);

    Fun(ptr);

}