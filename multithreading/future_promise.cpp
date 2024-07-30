#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>

std::promise<int> p1;
std::future<int> f1 = p1.get_future();
std::promise<int> p2;
std::future<int> f2 = p2.get_future();

std::mutex printMtx;

void func1()
{
	for(int i = 0; i< 100; i++ )
	{
		{
			std::lock_guard<std::mutex> lock(printMtx);
			std::cout<<"Thread 1: "<<i<<std::endl;
            if(i == 50)
                p1.set_value(i);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void func2()
{
    
	for(int i = f1.get(); i< 100; i++ )
	{
		{
			std::lock_guard<std::mutex> lock(printMtx);
			std::cout<<"\t\tThread 2: "<<i<<std::endl;
            if(i == 75)
                p2.set_value(i);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void func3()
{
    
	for(int i = f2.get(); i< 100; i++ )
	{
		{
			std::lock_guard<std::mutex> lock(printMtx);
			std::cout<<"\t\t\t\tThread 3: "<<i<<std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

int main()
{
    std::cout<<"Starting Thread 3\n";
    std::thread t3(func3);
    std::cout<<"Starting Thread 2\n";
    std::thread t2(func2);
    std::cout<<"Starting Thread 1\n";
	  std::thread t1(func1);
	
    t1.join();
    t2.join();
    t3.join();

	return 0;
}
