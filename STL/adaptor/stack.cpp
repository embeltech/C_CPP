#include <iostream>
#include <stack>
#include <string>

// stack -> LIFO -> it is container adaptor

int main()
{
    //initialization
    std::stack<std::string> stkData;
    
    stkData.push("1.My");   //adds element at the end of stack
    stkData.push("2.Name");
    stkData.push("3.Is");
    
    
    //size,resize empty check
    if(!stkData.empty())
    {
        std::cout<<"stkData Size : "<<stkData.size()<<std::endl;
    }
    else
    {
        std::cout<<"stack empty\n";
    }
    
    std::cout<<"stack unwinding\n";
    while(!stkData.empty())
    {
        std::cout<<stkData.top()<<std::endl;
        stkData.pop();
    }
    
    return 0;
}
