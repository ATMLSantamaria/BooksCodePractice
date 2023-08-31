/* 
Traits are a generic programming technique that allows compile-time decisions to be made based on types,
much as you would make runtime decisions based on values
 */

//Example of use
//I have a generic copying algorithm

template<typename InIt,typename OutIt>
OutIt Copy(InIt first,InIt last,OutIt result){
    for(;first!=last;++result){
        *result=*first;
    }
    //return result;
}
#include <cstdio>
//And i have a legacy very efficient algorithm for copying primitives types
void BitBlast(const void* src, void* dest, size_t bytes);

// I would like to implement Copy
// so as to take advantage of BitBlast whenever possible, and fall back on a more general, conservative
// algorithm for elaborate types

// What you need here are two tests:
// 1 - Are InIt and OutIt regular pointers (as opposed to fancier iterator types)?
// 2 - Is the type to which InIt and OutIt point copyable with bitwise copy?

// If you can find answers to these questions at compile time and if the answer to both questions is yes, you
// can use BitBlast . Otherwise, you must rely on the generic for loop.

//Type traits are the answer to this issue

int main(){

}

