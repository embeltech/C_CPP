#include <iostream>

template<typename T>
class shared_ptr {
private:
    T* mPtr;
    size_t* ref_count;
    
    // Utility function to decrement reference count
    //private function to protect from manipulating from outside of class
    void decrement_ref_count() {
        if(*ref_count > 0)
        {
            (*ref_count)--;
            std::cout<<"Ref count reduced\n";
        }
        if (*ref_count == 0) {
            if(mPtr)
                delete mPtr;
            mPtr = nullptr;
            if(ref_count)
                delete ref_count;
            ref_count = nullptr;
            std::cout<<"Object deleted\n";
        }
    }

public:
    // Constructor
    explicit shared_ptr(T* ptr = nullptr) : mPtr(ptr), ref_count(new size_t(0)) 
    {
        if(mPtr)
            (*ref_count)++;
        std::cout<<"CTOR\n";
    }

    // Destructor
    ~shared_ptr() {
        std::cout<<"DTOR\n";
        decrement_ref_count();
    }
    
    // Utility function to get reference count
    size_t use_count() const {
        if(ref_count)
            return *ref_count;
        else
            return 0;
    }

    // Copy constructor
    shared_ptr(const shared_ptr& other) : mPtr(other.mPtr), ref_count(other.ref_count) {
        (*ref_count)++;
        std::cout<<"Copy CTOR\n";
    }

    // copy Assignment operator
    void operator=(const shared_ptr& other) {
        if (this != &other) {
            decrement_ref_count();
            
            mPtr = other.mPtr;
            ref_count = other.ref_count;
            
            (*ref_count)++;
        }
        std::cout<<"Copy Assignment\n";
    }

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

    // Check if the pointer is null
    explicit operator bool() const {
        return bool(mPtr != nullptr);
    }
    
    void reset(T* ptr=nullptr)
    {
        std::cout<<"reset\n";
        decrement_ref_count();
        mPtr = ptr;
        if(mPtr)
        {
            ref_count = new size_t(1);
        }
    }

};


int main() {
    shared_ptr<int> ptr1(new int(10));
    std::cout << "use_count: " << ptr1.use_count() << std::endl;

    {
        shared_ptr<int> ptr2 = ptr1;
        std::cout << "use_count: " << ptr1.use_count() << std::endl;
        std::cout << "use_count: " << ptr2.use_count() << std::endl;
    }

    std::cout << "use_count: " << ptr1.use_count() << std::endl;
    std::cout << "*ptr1: " << *ptr1 << std::endl;
    shared_ptr<int> ptr3 = ptr1;
    std::cout << "*ptr3: " << *ptr3 << std::endl;
    std::cout << "use_count ptr3: " << ptr3.use_count() << std::endl;
    shared_ptr<int> ptr4(new int(100));
    ptr3.reset(ptr4.get());
    std::cout << "use_count ptr3: " << ptr3.use_count() << std::endl;
    std::cout << "*ptr3: " << *ptr3 << std::endl;

    return 0;
}
