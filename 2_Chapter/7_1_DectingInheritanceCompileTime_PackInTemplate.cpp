//Implement all the ideas of the file 7 but packed in a template

template<class U, class T>
class Conversion{
    typedef char Small;
    class Big{char dummy[2];};

    //Overload functions to return different types in function of the possibility of conversion of T into U
    static Small Test(U);
    static Big Test(...);

    //Function necessary to use T in case its constructor is private
    static T MakeT();

    public:
    enum{exist=
         sizeof( Test(MakeT())) == sizeof(Small) };

};

#include <iostream>
#include <vector>
int main(){
    std::cout 
                << Conversion<double,int>::exist << " "
                << Conversion<char,char*>::exist << " "
                << Conversion<std::vector<int>,std::vector<int>>::exist<< " "
                << Conversion<std::vector<double>,std::vector<int>>::exist <<
                std::endl;

            
}