#include <iostream>
#include <unordered_set>
#include <string>


// unorderd_set-> unique & Not sorted elements which cannot be modified. Only can be removed or added.

void printSet(const std::unordered_set<std::string>& setData)
{
    std::cout<<"----------------------------\n";
    for(auto entry:setData)
    {
        std::cout<<entry<<std::endl;
    }
}

int main()
{
    std::unordered_set<std::string> mUniqueData;
    
    //insert new element hard coded.
    mUniqueData.insert("Fname lname");
    mUniqueData.insert("PQR");
    mUniqueData.insert("ABC XYZ");
    
    //insert operation results: results.second is true if success else false.
    std::string strName("PQR");
    auto result = mUniqueData.insert(strName);
    if(result.second)
        std::cout<<"Iter >> "<<"Inserted : "<<*result.first<<std::endl;
    else
        std::cout<<"Key Exists\n";
    printSet(mUniqueData);
    
    //size, empty check
    if(!mUniqueData.empty())
    {
        std::cout<<"Size : "<<mUniqueData.size()<<std::endl;
    }
    else
    {
        std::cout<<"PhoneBook empty\n";
    }
    
    //find key
    //std::set<std::string>::iterator iter = mUniqueData.find("NAME");
    auto iter = mUniqueData.find("ABC XYZ");
    if(iter != mUniqueData.end())
    {
        std::cout<<"Found >> "<<"Name : "<<*iter<<std::endl;
    }
    else
    {
        std::cout<<"Not found\n";
    }
    
    //Check if key present. count().
    if(mUniqueData.count("PQR") > 0)
    {
        std::cout<<"Key present: PQR\n";
    }
    
    //erase element using iterator
    if(iter != mUniqueData.end())
    {
        mUniqueData.erase(iter);
        printSet(mUniqueData);
    }
    
    //erase element using key
    mUniqueData.erase("PQR");
    printSet(mUniqueData);
    
    //Remove all elements
    mUniqueData.clear();
    //size, empty check
    if(!mUniqueData.empty())
    {
        std::cout<<"After Clear.Size : "<<mUniqueData.size()<<std::endl;
    }
    else
    {
        std::cout<<"After Clear.PhoneBook empty\n";
    }
    
    return 0;
}
