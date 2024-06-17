#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    std::vector<int> vect{1,2,3,4};
    std::cout<<"Hello World\n";
    int var = 10;
    transform(vect.begin(),vect.end(),vect.begin(),[var](int a){return a*a*var;});
       
   
    for(auto x:vect)
    std::cout<<x<<" ";

    return 0;
}
