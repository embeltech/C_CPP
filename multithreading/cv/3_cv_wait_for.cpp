/*
* bool bIsCondMet = cv.wait_for(lock, <timeout>, <lambda_to_handle_spurious_wakeup>)
* bIsCondMet = true -> condition met and wait is over , no timeout occured 
* bIsCondMet = false -> condition NOT met, TIMEOUT occured
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
            //simulate thread stuck/taking more time than timeout defined for condition variable
            std::this_thread::sleep_for(std::chrono::seconds(5));
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
    bool bIsCondMet = cond_var.wait_for(uCondLock, std::chrono::seconds(2), []{ return shared_variable==9; });
    uCondLock.unlock();
    if(bIsCondMet)
    {
        // bIsCondMet is true means condition met
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
    else
    {
      // bIsCondMet is false means timeout occured
      std::cout<<"TIMEOUT occured for Thread2\n";
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
