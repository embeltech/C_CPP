#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mtx;

int shared_variable = 0;
void func(int id, char c)
{
    for(int i = 0; i<20; i++)
    {
        mtx.lock();
        shared_variable++;
        std::cout<<"Thread "<<id<<c<<" : shared_variable = "<<shared_variable<<"\n";
        mtx.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main()
{
    // thread (thread function, function parameters)
    std::thread t1(func,1,'A');
    std::thread t2(func,2,'B');
    
    t1.join();// or t1.detach();
    t2.join();// or t2.detach();
    
   
    return 0;
}
