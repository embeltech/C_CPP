#include <iostream>
#include <vector>
#include <string>


void printVector(const std::vector<std::string>& vect)
{
    std::cout<<"----------------------------\n";
    for(auto entry:vect)
    {
        std::cout<<entry<<std::endl;
    }
}

int main()
{
    //initialization
    std::vector<std::string> vectData(3,"Hi");
    
    vectData.push_back("My");   //adds element at the end of vector
    vectData.push_back("Name");
    vectData.push_back("Is");
    
    printVector(vectData);
    
    auto iter = vectData.begin();
    //insert new element hard coded.After insertion get new iter as old one is not valid
    iter = vectData.insert(iter,"ABC");
    iter = vectData.insert(iter+3,"PQR");
    iter = vectData.insert(vectData.end(),"XYZ");
    
    printVector(vectData);

    
    //size,capacity,resize empty check
    if(!vectData.empty())
    {
        std::cout<<"Vector Size : "<<vectData.size()<<std::endl;
        std::cout<<"Vector Capacity : " << vectData.capacity()<<std::endl;
    }
    else
    {
        std::cout<<"Vector empty\n";
    }
    
    //Random access 
    std::cout<<"vector data at 0 : "<<vectData[0]<<std::endl;
    std::cout<<"vector data at 1 : "<<vectData.at(1)<<std::endl;
    std::cout<<"vector data at front(vectData.begin()) : "<<vectData.front()<<std::endl;
    std::cout<<"vector data at back(vectData.end()-1) : "<<vectData.back()<<std::endl;

    
    //Remove elements
    printVector(vectData);
    std::cout<<"After pop_back\n";
    vectData.pop_back();
    printVector(vectData);
    
    
    //find not supported in vector
    //std::vector<std::string>::iterator iter = vectData.begin();
    for(auto iter = vectData.begin(); iter !=vectData.end(); iter++)
        if(*iter == "PQR")
        {
            std::cout<<"Found PQR.Erase It"<<std::endl;
            vectData.erase(iter);
            break;
        }
    printVector(vectData);
    
    //Remove all elements
    vectData.clear();
    //size, empty check
    if(!vectData.empty())
    {
        std::cout<<"After Clear.Size : "<<vectData.size()<<std::endl;
    }
    else
    {
        std::cout<<"After Clear.vector empty\n";
    }
    
    return 0;
}
