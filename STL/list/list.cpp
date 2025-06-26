#include <iostream>
#include <list>
#include <string>

//list -> doubly linkedlist
void printList(const std::list<std::string>& lst)
{
    std::cout<<"----------------------------\n";
    for(auto entry:lst)
    {
        std::cout<<entry<<std::endl;
    }
}
//predicate returning bool
bool remover(const std::string & str)
{
    return (str.size() < 3);
}

int main()
{
    //initialization
    std::list<std::string> lstData;
    
    lstData.push_back("My");   //adds element at the end of vector
    lstData.push_back("Name");
    lstData.push_back("Is");
    lstData.push_back("OOO");
    lstData.push_front("Hi");
    lstData.push_back("ABC");
    lstData.push_front("OOO");
    
    
    printList(lstData);
    
    auto iter = lstData.begin();
    //insert new element hard coded.After insertion get new iter as old one is not valid
    iter = lstData.insert(iter,"ABC");
    iter = lstData.insert(iter,"PQR");
    iter = lstData.insert(lstData.end(),"XYZ");
    
    printList(lstData);

    
    //size, empty check
    if(!lstData.empty())
    {
        std::cout<<"list Size : "<<lstData.size()<<std::endl;
    }
    else
    {
        std::cout<<"List empty\n";
    }
    
    //Random access not allowed for list
    std::cout<<"List data at front(lstData.begin()) : "<<lstData.front()<<std::endl;
    std::cout<<"List data at back(lstData.end()-1) : "<<lstData.back()<<std::endl;

    
    //Remove elements
    printList(lstData);
    std::cout<<"After pop_back\n";
    lstData.pop_back();
    printList(lstData);
    std::cout<<"After pop_front\n";
    lstData.pop_front();
    printList(lstData);
    
    //remove by key. Removes all occurences
    lstData.remove("OOO");
    std::cout<<"Removed OOO\n";
    printList(lstData);
    
    //remove by predicate
    lstData.remove_if(remover);
    std::cout<<"After Remover\n";
    printList(lstData);
    
    //find not supported in list
    //std::vector<std::string>::iterator iter = vectData.begin();
    for(auto iter = lstData.begin(); iter !=lstData.end(); iter++)
        if(*iter == "ABC")
        {
            std::cout<<"Found ABC.Erase It"<<std::endl;
            lstData.erase(iter);
            break;
        }
    printList(lstData);
    
    //Remove all elements
    lstData.clear();
    //size, empty check
    if(!lstData.empty())
    {
        std::cout<<"After Clear.Size : "<<lstData.size()<<std::endl;
    }
    else
    {
        std::cout<<"After Clear.list empty\n";
    }
    
    return 0;
}
