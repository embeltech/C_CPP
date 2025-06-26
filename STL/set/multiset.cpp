#include <iostream>
#include <set>
#include <string>


// multiset-> Not unique & sorted elements which cannot be modified. Only can be removed or added.

void printSet(const std::multiset<std::string>& setData)
{
    std::cout<<"----------------------------\n";
    for(auto entry:setData)
    {
        std::cout<<entry<<std::endl;
    }
}

int main()
{
    std::multiset<std::string> mSetData;
    
    //insert new element hard coded.
    mSetData.insert("Fname lname");
    mSetData.insert("PQR");
    mSetData.insert("ABC XYZ");
    
    //insert operation results: result is iterator to newly inserted.
    std::string strName("PQR");
    auto result = mSetData.insert(strName);
    std::cout<<"Iter >> "<<"Inserted : "<<*result<<std::endl;
    printSet(mSetData);
    
    //size, empty check
    if(!mSetData.empty())
    {
        std::cout<<"Size : "<<mSetData.size()<<std::endl;
    }
    else
    {
        std::cout<<"PhoneBook empty\n";
    }
    
    //find key
    //std::set<std::string>::iterator iter = mUniqueData.find("NAME");
    auto iter = mSetData.find("ABC XYZ");
    if(iter != mSetData.end())
    {
        std::cout<<"Found >> "<<"Name : "<<*iter<<std::endl;
    }
    else
    {
        std::cout<<"Not found\n";
    }
    
    //Check if key present. count().
    if(mSetData.count("PQR") > 0)
    {
        std::cout<<"Key present: PQR\n";
    }
    
    //erase element using iterator
    if(iter != mSetData.end())
    {
        mSetData.erase(iter);
        printSet(mSetData);
    }
    
    //erase element using key. erases all elements mentioned by key.
    mSetData.erase("PQR");
    printSet(mSetData);
    
    //Remove all elements
    mSetData.clear();
    //size, empty check
    if(!mSetData.empty())
    {
        std::cout<<"After Clear.Size : "<<mSetData.size()<<std::endl;
    }
    else
    {
        std::cout<<"After Clear.PhoneBook empty\n";
    }
    
    return 0;
}
