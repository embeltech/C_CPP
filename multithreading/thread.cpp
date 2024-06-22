#include <iostream>
#include <thread>    //under the hood lpthread is used.
#include <unistd.h> //sleep for linux 

void func(int id, char c)
{
    for(int i = 0; i<20; i++)
    std::cout<<"Thread "<<id<<c<<" : i = "<<i<<std::endl;
    usleep(10000);
}


int main()
{
    // thread (thread function, function parameters)
    std::thread t1(func,1,'A');
    std::thread t2(func,2,'B');
    
    t1.join();
    t2.join();
    
   
    return 0;
}
