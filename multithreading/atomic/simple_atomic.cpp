/*
*  Like Atoms (are indivisible?), Atomic Operations are guaranteed to be performed as a single, indivisible operation.
*  Lock-Free: Many atomic operations are lock-free, As they do not require locking mechanisms/mutexes code is clean and light.
*  Memory Ordering: std::atomic provides various memory ordering options to control the visibility of operations across threads.
*  --> TODO : Memory Ordering
*
*/

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> atomicCounter(0);

void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        //No mutex required 
        atomicCounter++;
    }
}

int main() {
    std::vector<std::thread> threads;

    // Create 10 threads that increment the counter
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(incrementCounter));
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }
    //IMP .load() function to read automic variable
    std::cout << "Final counter value: " << atomicCounter.load() << std::endl;
    //Final counter value: 10000
    return 0;
}
