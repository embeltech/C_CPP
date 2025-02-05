/*
*  std::async is a template function provided by the C++ Standard Library (STL)
*  It allows you to run a function asynchronously (inside separate thread)
*  The std::async function returns a std::future object, which can be used to retrieve the result of the asynchronous operation once it is complete.
*  std::async(<launch_policy>, function name, argumrnts..)
*  Launch Policy:
*    std::launch::async: The function is run asynchronously on a new thread.
*    std::launch::deferred: The function is run synchronously when the result is requested.
*/


#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Function to be executed asynchronously
int computeSum(int a, int b) 
{
	std::cout << "Async Running" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate a long computation
	std::cout << "Result Ready" << std::endl;
	return a + b;
}

int main() {
    // Run computeSum asynchronously
    std::future<int> result = std::async(std::launch::async, computeSum, 5, 10);

    // Do other work while computeSum is running
    std::cout << "Doing other work... 2 sec" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Getting result" << std::endl;
    // Get the result of the asynchronous operation
    int sum = result.get(); // This will block until the result is ready

    std::cout << "The sum is: " << sum << std::endl;

    return 0;
}

/**************************************
std::async(std::launch::async, computeSum, 5, 10);
Doing other work... 2 sec
  Async Running
  Result Ready
Getting result
The sum is: 15

**************************************
std::async(std::launch::deferred, computeSum, 5, 10);
Doing other work... 2 sec
Getting result
  Async Running
  Result Ready
The sum is: 15

***************************************/
