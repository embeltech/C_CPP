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
        {
            std::lock_guard<std::mutex> lgLock(mtx);
            shared_variable++;
            std::cout<<"Thread "<<id<<c<<" : shared_variable = "<<shared_variable<<"\n";

        } //these paranthesis required so that lgLock object is destroyed when goes out of scope and mutex is unlocked automatically.
        // lock_guard object cannot be unlocked manually. It gurantees unlock in case of exceptions but useful for automatic/short duration objects
        // unique_lock can be used if paranthesis needs to be removed and explicit lock unlock can be called.
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
