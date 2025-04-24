#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
// Condition variable has to be associated with mutex
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
    cond_var.wait(uCondLock);
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
