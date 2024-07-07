//supported in CPP14 onwards
#include <iostream> 
#include <string> 

int setValue(int x)
{
    return x*x;
}

int main() 
{ 

	// Declare a generalized lambda and store it in sum
	auto sum = [](auto a, auto b) { return a + b; }; 

	// Find sum of two integers 
	std::cout << sum(1, 6) << std::endl; 

	// Find sum of two floating numbers 
	std::cout << sum(1.0, 5.6) << std::endl; 

	// Find sum of two strings 
	std::cout << sum(std::string("TTL "), std::string("BMW")) << std::endl; 

    //---------------------------------------------------
    //generalised lambda capture. Captured once when lambda is declared. No need of datatype for captured variable.
    auto iter = [counter = setValue(10)]()mutable { return ++counter;};
    
    int value = 0;
    //range for loop
    for(int i : {1,2,3,4,5})
    {
        value = iter();
        std::cout<<i<<":"<<value<<std::endl;
    }
    
	return 0; 
} 
