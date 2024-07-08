#include <iostream>

template<typename T>
class unique_ptr {
private:
    T* ptr;

public:
    // Constructor
    explicit unique_ptr(T* ptr = nullptr) : ptr(ptr) {}

    // Destructor
    ~unique_ptr() {
        delete ptr;
    }

    // Move constructor
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Move assignment operator
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Disable copy operations
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

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
};

int main() {
    unique_ptr<int> ptr1(new int(10));
    std::cout << "*ptr1: " << *ptr1 << std::endl;

    unique_ptr<int> ptr2 = std::move(ptr1);
    std::cout << "*ptr2: " << *ptr2 << std::endl;

    // Accessing ptr1 here would result in undefined behavior since it's been moved from
    // std::cout << "*ptr1: " << *ptr1 << std::endl;

    return 0;
}
