#include <initializer_list> 
#include <iostream> 
#include <string>
#include <vector>
template<typename T>
void printList(std::initializer_list<T> lst)    //initializer list as function parameter
{
    std::cout<<"Size of list : "<<lst.size()<<std::endl;
   
    std::vector<T> vect = lst;  //initializer list as initializer for STL container
    for(auto item: vect)
        std::cout<<item<<" ";
    std::cout<<std::endl;
    
}


int main() 
{ 
	// Initializing an object using initializer_list 
	std::initializer_list<int> lstNum = {1,2,3,4,5} ; 
	std::initializer_list<std::string> lstStrings = { "Hi","Hello","welcome" }; 

    printList(lstNum);
    printList(lstStrings);
	return 0; 
}
