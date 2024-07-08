#include <iostream>

template<typename T>
class shared_ptr {
private:
    T* ptr;
    size_t* ref_count;

public:
    // Constructor
    explicit shared_ptr(T* ptr = nullptr) : ptr(ptr), ref_count(new size_t(1)) {}

    // Destructor
    ~shared_ptr() {
        decrement_ref_count();
    }

    // Copy constructor
    shared_ptr(const shared_ptr& other) : ptr(other.ptr), ref_count(other.ref_count) {
        (*ref_count)++;
    }

    // Assignment operator
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            decrement_ref_count();
            ptr = other.ptr;
            ref_count = other.ref_count;
            (*ref_count)++;
        }
        return *this;
    }

    // Dereferencing operator
    T& operator*() const {
        return *ptr;
    }

    // Member access operator
    T* operator->() const {
        return ptr;
    }

    // Get raw pointer
    T* get() const {
        return ptr;
    }

    // Check if the pointer is null
    explicit operator bool() const {
        return ptr != nullptr;
    }

    // Utility function to get reference count
    size_t use_count() const {
        return *ref_count;
    }

private:
    // Utility function to decrement reference count
    void decrement_ref_count() {
        (*ref_count)--;
        if (*ref_count == 0) {
            delete ptr;
            delete ref_count;
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

    return 0;
}

