#include <iostream>
#include <queue>
#include <string>

// queue -> FIFO -> it is container adaptor

int main()
{
    //initialization
    std::queue<std::string> qData;
    
    qData.push("1.My");   //adds element at the end of stack
    qData.push("2.Name");
    qData.push("3.Is");
    
    
    //size,resize empty check
    if(!qData.empty())
    {
        std::cout<<"stkData Size : "<<qData.size()<<std::endl;
    }
    else
    {
        std::cout<<"Queue empty\n";
    }
    
    std::cout<<"Queue Entries\n";
    while(!qData.empty())
    {
        std::cout<<qData.front()<<std::endl;
        qData.pop();
    }
    
    return 0;
}
