#include <iostream>

template<typename T>
class unique_ptr {
private:
    T* mPtr;

public:
    // Constructor
    explicit unique_ptr(T* ptr = nullptr) : mPtr(ptr) {
         std::cout<<"CTOR\n";
    }

    // Destructor
    ~unique_ptr() {
        if(mPtr)
        {
            delete mPtr;
            mPtr = nullptr;
            
        }
        std::cout<<"DTOR\n";
    }
    
    // Disable copy operations
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Dereferencing operator
    T& operator*() const {
        return *mPtr;
    }

    // Member access operator
    T* operator->() const {
        return mPtr;
    }

    // Get raw pointer
    T* get() const {
        return mPtr;
    }

    // Move constructor
    unique_ptr(unique_ptr&& other) noexcept : mPtr(other.mPtr) {
        //no need to delete mPtr as object is under construction so mPtr does not point to any object
        other.mPtr = nullptr;
        std::cout<<"Move CTOR\n";
    }

    // Move assignment operator
    void operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete mPtr;
            mPtr = other.mPtr;
            other.mPtr = nullptr;
            std::cout<<"Move assignment\n";
        }
    }

    // Check if the pointer is null
    explicit operator bool() const {
        std::cout<<"bool "<<(mPtr != nullptr)<<"\n";
        return bool(mPtr != nullptr);
    }
    
    void reset(T* ptr=nullptr)
    {
        if(mPtr)
        {
            delete mPtr;
            mPtr = ptr;
            std::cout<<"reset\n";
        }
    }
    T* release()
    {
        T* temp = nullptr;
        if(mPtr)
        {
            temp = mPtr;
            mPtr = nullptr;
            std::cout<<"release\n";
        }
        return temp;
    }
        
};

int main() {
    unique_ptr<int> ptr1(new int(10));
    std::cout << "*ptr1: " << *ptr1 << std::endl;

    unique_ptr<int> ptr2(std::move(ptr1));
    std::cout << "*ptr2: " << *ptr2 << std::endl;

    if(!ptr1)
    {
        std::cout<<"ptr1 is null\n";
        ptr1=std::move(ptr2);
        std::cout << "*ptr1: " << *ptr1 << std::endl;
    }
    else
    {
        std::cout<<"else";
    }
    ptr1.reset();
    
    unique_ptr<int> ptr3(new int(1000));
    unique_ptr<int> ptr4(new int(10000));
    std::cout << "*ptr3: " << *ptr3 << std::endl;
    std::cout << "*ptr4: " << *ptr4 << std::endl;
    
    ptr3.reset(ptr4.release());
    std::cout << "*ptr3: " << *ptr3 << std::endl;
    

    return 0;
}
