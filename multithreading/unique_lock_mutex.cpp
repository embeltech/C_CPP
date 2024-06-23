#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mtx;

int shared_variable = 0;
void func(int id, char c)
{
    // deferred locking. create object but do not lock mutex at the time of creation.
    //std::unique_lock<std::mutex> uLock(mtx,std::defer_lock);
    for(int i = 0; i<20; i++)
    {
       
        std::unique_lock<std::mutex> uLock(mtx); // lock mutex when uLock obj is created.
        
        //uLock.lock(); //unique lock can be explicitly locked whenever required when used with defer_lock at the time of lock object creation.
        shared_variable++;
        std::cout<<"Thread "<<id<<c<<" : shared_variable = "<<shared_variable<<"\n";

        uLock.unlock(); //unique lock is same as lock guard with additinal functionality of explicit/manual lock,unlock
        
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
