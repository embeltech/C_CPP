#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std::placeholders;

int inc(int x,int y)
{
    return x*x*y;
}
int main()
{
    std::vector<int> vect{1,2,3,4};
    std::cout<<"Hello World\n";
   
    int var = 10;
    auto func = std::bind(inc,_1,var);
   
    transform(vect.begin(),vect.end(),vect.begin(),func);
       
   
    for(auto x:vect)
    std::cout<<x<<" ";

    return 0;
}
