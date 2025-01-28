#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    std::vector<int> vect{1,2,3,4};
    std::cout<<"Hello World\n";
    int var = 10;
    transform(vect.begin(),vect.end(),vect.begin(),[var](int a){return a*a*var;});
    //main purpose of lambda is to pass more parameters to predicate function.
    //It can also be achieved by std::bind, functors
   
    for(auto x:vect)
    std::cout<<x<<" ";

    return 0;
}

/*********************************************************************************************************************

Capture by Value: 
- Captures a copy of the variable.
- By default case of capture.
- Capture takes place once at the time of declaration of lambda. 
- Any change in captured variable after declaration of lambda will not affect captured value inside lambda

Capture by Reference: 
- Captures a reference to the variable
- Any change in captured variable even after declaration of lambda will affect captured value inside lambda

Capture All by Value: 
- Captures all variables in the enclosing scope by value.
- auto lambda = [=]() { body of lambda };

Capture All by Reference: 
- Captures all variables in the enclosing scope by reference
- auto lambda = [&]() { body of lambda };

Mixed Capture
- Capture x by value and y by reference.
- auto lambda = [x,&y]() { body of lambda };

- Capture x by value and all remaining by reference.
- auto lambda = [x,&]() { body of lambda };

- Capture x by reference and all remaining by value.
- auto lambda = [&x,=]() { body of lambda };


*/
