#include <iostream>
#include <map>
#include <string>


// map-> unique and sorted keys
//If new key value pair is added which has same key the mapped value is overwritten with new value

void printMap(const std::map<std::string,std::string>& mapData)
{
    std::cout<<"----------------------------\n";
    for(auto entry:mapData)
    {
        std::cout<<entry.first <<"\t"<<entry.second<<std::endl;
    }
}

int main()
{
    std::map<std::string,std::string> mPhonebook;
    
    //insert new element hard coded.
    mPhonebook["fname lname"] = "1234567890";
    mPhonebook["PQR"] = "1234567890";
    mPhonebook.insert(std::pair<std::string,std::string>("ABC XYZ","1111122222"));
    
    //insert operation results: results.second is true if success else false.
    std::string strName("MyFN LN"), strNum("3333344444");
    auto result = mPhonebook.insert(std::pair<std::string,std::string>(strName,strNum));
    if(result.second)
        std::cout<<"Iter >> "<<"Name : "<<result.first->first<<"| Number : "<<result.first->second<<std::endl;
    
    printMap(mPhonebook);
    
    //size, empty check
    if(!mPhonebook.empty())
    {
        std::cout<<"Size : "<<mPhonebook.size()<<std::endl;
    }
    else
    {
        std::cout<<"PhoneBook empty\n";
    }
    
    //find key
    //std::map<std::string,std::string>::iterator iter = mPhonebook.find("NAME");
    auto iter = mPhonebook.find("ABC XYZ");
    if(iter != mPhonebook.end())
    {
        std::cout<<"Found >> "<<"Name : "<<iter->first<<"| Number : "<<iter->second<<std::endl;
    }
    else
    {
        std::cout<<"Not found\n";
    }
    
    //Check if key present. count().
    if(mPhonebook.count("PQR") > 0)
    {
        std::cout<<"Key present: PQR\n";
    }
    
    //erase element using iterator
    if(iter != mPhonebook.end())
    {
        mPhonebook.erase(iter);
        printMap(mPhonebook);
    }
    
    //erase element using key
    mPhonebook.erase("PQR");
    printMap(mPhonebook);
    
    //Remove all elements
    mPhonebook.clear();
    //size, empty check
    if(!mPhonebook.empty())
    {
        std::cout<<"After Clear.Size : "<<mPhonebook.size()<<std::endl;
    }
    else
    {
        std::cout<<"After Clear.PhoneBook empty\n";
    }
    
    return 0;
}
