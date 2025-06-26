#include <iostream>
#include <deque>
#include <string>

// deque -> similar to vector but provides efficient insertion and deletion of elements at the beginning of the sequence
// in addition to end
void printDeque(const std::deque<std::string>& deq)
{
    std::cout<<"----------------------------\n";
    for(auto entry:deq)
    {
        std::cout<<entry<<std::endl;
    }
}

int main()
{
    //initialization
    std::deque<std::string> deqData(3,"Hi");
    
    deqData.push_back("My");   //adds element at the end of deque
    deqData.push_back("Name");
    deqData.push_back("Is");
    
    printDeque(deqData);
    
    auto iter = deqData.begin();
    //insert new element hard coded.After insertion get new iter as old one is not valid
    iter = deqData.insert(iter,"ABC");
    iter = deqData.insert(iter+3,"PQR");
    iter = deqData.insert(deqData.end(),"XYZ");
    
    printDeque(deqData);

    
    //size,resize empty check
    if(!deqData.empty())
    {
        std::cout<<"deqData Size : "<<deqData.size()<<std::endl;
    }
    else
    {
        std::cout<<"Vector empty\n";
    }
    
    //Random access 
    std::cout<<"deqData data at 0 : "<<deqData[0]<<std::endl;
    std::cout<<"deqData data at 1 : "<<deqData.at(1)<<std::endl;
    std::cout<<"deqData data at front(deqData.begin()) : "<<deqData.front()<<std::endl;
    std::cout<<"deqData data at back(deqData.end()-1) : "<<deqData.back()<<std::endl;

    
    //Remove elements
    printDeque(deqData);
    std::cout<<"After pop_back\n";
    deqData.pop_back();
    printDeque(deqData);
    std::cout<<"After pop_front\n";
    deqData.pop_front();
    printDeque(deqData);
    
    
    //find not supported in vector
    //std::vector<std::string>::iterator iter = deqData.begin();
    for(auto iter = deqData.begin(); iter !=deqData.end(); iter++)
        if(*iter == "PQR")
        {
            std::cout<<"Found PQR.Erase It"<<std::endl;
            deqData.erase(iter);
            break;
        }
    printDeque(deqData);
    
    //Remove all elements
    deqData.clear();
    //size, empty check
    if(!deqData.empty())
    {
        std::cout<<"After Clear.Size : "<<deqData.size()<<std::endl;
    }
    else
    {
        std::cout<<"After Clear.deqData empty\n";
    }
    
    return 0;
}
