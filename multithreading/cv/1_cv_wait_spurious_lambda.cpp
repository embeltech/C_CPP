/*
* What is a Spurious Wakeup?
* A spurious wakeup is a phenomenon in multithreaded programming 
* where a thread that is waiting on a condition variable is awakened without any explicit signal or notification. 
* This means that the thread may be woken up even though the condition it is waiting for has not been met. 
* 
* Why Do Spurious Wakeups Occur?
* Spurious wakeups can occur due to various reasons, including:
* Hardware Interrupts: Certain hardware events or interrupts can cause a thread to wake up unexpectedly.
* Operating System Scheduling: The operating system's scheduler may cause a thread to wake up due to internal optimizations or anomalies.
* Race Conditions: In some cases, race conditions in the implementation of condition variables can lead to spurious wakeups.
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::mutex mtx_cond;
std::condition_variable cond_var;

int shared_variable = 0;
void func1(int id, char c)
{
    for(int i = 0; i<20; i++)
    {
        std::unique_lock<std::mutex> uLock(mtx);
        shared_variable++;
        std::cout<<"Thread "<<id<<c<<" : shared_variable = "<<shared_variable<<"\n";
        uLock.unlock();

        if(i == 9)
        {
            std::cout<<"Signaling Thraed 2"<<std::endl;
            std::unique_lock<std::mutex> uCondLock(mtx_cond);
            cond_var.notify_all();
            uCondLock.unlock();
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void func2(int id, char c)
{
    std::unique_lock<std::mutex> uCondLock(mtx_cond);
    //wait till shared_variable=9. 
    //So any spurious wakeup will check shared_variable==9 condition. If its true then only it will come out of wait. Else remain in wait. 
    cond_var.wait(uCondLock, []{ return shared_variable==9; });
    uCondLock.unlock();
    std::cout<<"Wait Over for Thread2\n";

    for(int i = 0; i<20; i++)
    {
        std::unique_lock<std::mutex> uLock(mtx);
        shared_variable++;
        std::cout<<"Thread "<<id<<c<<" : shared_variable = "<<shared_variable<<"\n";
        uLock.unlock();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}


int main()
{
    // thread (thread function, function parameters)
    std::thread t1(func1,1,'A');
    std::thread t2(func2,2,'B');
    
    t1.join();// or t1.detach();
    t2.join();// or t2.detach();
    
   
    return 0;
}
