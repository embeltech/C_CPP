
#include <iostream>
#include <string>
#include <functional>

void print(std::string& str)
{
    std::cout<<str<<std::endl;
}

int main()
{
    std::string s = "Function call print";
    print(s);

    void (*fptr)(std::string& str) = print;
    s = "Function call print using fptr";
    fptr(s);
    
    //using std::function as alternative for function pointer
    std::function<void(std::string&)> stdfunc = print;
    s = "Function call print using std::function";
    stdfunc(s);
    
    //std::function can be used as wrapper for any callable object : functor,lambda
    //----> defining lambda without auto
    std::function<bool(int)> lfunc = [](int x){ if(x>10) return true; else return false;} ;
    std::cout<<"lfunc : "<<lfunc(25)<<std::endl;
    return 0;
}
