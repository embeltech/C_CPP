#include <iostream>

template<typename T>
class shared_ptr; // Forward declaration for mutual dependency

template<typename T>
class weak_ptr {
private:
    T* ptr;
    size_t* ref_count;
    size_t* weak_count;

public:
    // Constructor
    weak_ptr() : ptr(nullptr), ref_count(nullptr), weak_count(nullptr) {}

    // Constructor from shared_ptr
    explicit weak_ptr(const shared_ptr<T>& shared) 
        : ptr(shared.ptr), ref_count(shared.ref_count), weak_count(shared.weak_count) {
        if (weak_count) {
            (*weak_count)++;
        }
    }

    // Copy constructor
    weak_ptr(const weak_ptr& other)
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        if (weak_count) {
            (*weak_count)++;
        }
    }

    // Move constructor
    weak_ptr(weak_ptr&& other) noexcept
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
        other.weak_count = nullptr;
    }

    // Destructor
    ~weak_ptr() {
        reset();
    }

    // Assignment operator
    weak_ptr& operator=(const weak_ptr& other) {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            if (weak_count) {
                (*weak_count)++;
            }
        }
        return *this;
    }

    // Move assignment operator
    weak_ptr& operator=(weak_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
            other.weak_count = nullptr;
        }
        return *this;
    }

    // Check if expired
    bool expired() const {
        return use_count() == 0;
    }

    // Lock to obtain shared_ptr
    shared_ptr<T> lock() const {
        if (!expired()) {
            return shared_ptr<T>(*this);
        } else {
            return shared_ptr<T>();
        }
    }

    // Reset weak_ptr
    void reset() {
        if (weak_count) {
            (*weak_count)--;
            if (*weak_count == 0) {
                delete ptr;
                delete ref_count;
                delete weak_count;
            }
        }
        ptr = nullptr;
        ref_count = nullptr;
        weak_count = nullptr;
    }

    // Get use count
    size_t use_count() const {
        if (ref_count) {
            return *ref_count;
        } else {
            return 0;
        }
    }

    // Get weak count
    size_t weak_count_use() const {
        if (weak_count) {
            return *weak_count;
        } else {
            return 0;
        }
    }

    // Friend declaration for shared_ptr
    friend class shared_ptr<T>;
};

// Define shared_ptr for mutual dependency
template<typename T>
class shared_ptr {
private:
    T* ptr;
    size_t* ref_count;
    size_t* weak_count;

public:
    explicit shared_ptr(T* ptr = nullptr)
        : ptr(ptr), ref_count(new size_t(ptr ? 1 : 0)), weak_count(new size_t(ptr ? 1 : 0)) {}

    // Constructor from weak_ptr
    shared_ptr(const weak_ptr<T>& weak)
        : ptr(weak.ptr), ref_count(weak.ref_count), weak_count(weak.weak_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    // Destructor
    ~shared_ptr() {
        decrement_ref_count();
    }

    // Copy constructor
    shared_ptr(const shared_ptr& other)
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    // Move constructor
    shared_ptr(shared_ptr&& other) noexcept
        : ptr(other.ptr), ref_count(other.ref_count), weak_count(other.weak_count) {
        other.ptr = nullptr;
        other.ref_count = nullptr;
        other.weak_count = nullptr;
    }

    // Assignment operator
    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            decrement_ref_count();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            if (ref_count) {
                (*ref_count)++;
            }
        }
        return *this;
    }

    // Move assignment operator
    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            decrement_ref_count();
            ptr = other.ptr;
            ref_count = other.ref_count;
            weak_count = other.weak_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
            other.weak_count = nullptr;
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

    // Get use count
    size_t use_count() const {
        if (ref_count) {
            return *ref_count;
        } else {
            return 0;
        }
    }

private:
    // Utility function to decrement reference count
    void decrement_ref_count() {
        if (ref_count) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete ptr;
                delete ref_count;
                if (weak_count) {
                    (*weak_count)--;
                    if (*weak_count == 0) {
                        delete weak_count;
                    }
                }
            }
        }
    }

    // Friend declaration for weak_ptr
    friend class weak_ptr<T>;
};

int main() {
    shared_ptr<int> ptr(new int(10));
    weak_ptr<int> weak(ptr);

    std::cout << "use_count of shared_ptr: " << ptr.use_count() << std::endl;
    std::cout << "weak_count of weak_ptr: " << weak.weak_count_use() << std::endl;

    {
        auto locked = weak.lock();
        if (locked) {
            std::cout << "Value via locked shared_ptr: " << *locked << std::endl;
            std::cout << "use_count of locked shared_ptr: " << locked.use_count() << std::endl;
        } else {
            std::cout << "Object expired." << std::endl;
        }
    }

    //ptr.reset(); // Release shared_ptr

    std::cout << "use_count of shared_ptr after reset: " << ptr.use_count() << std::endl;
    std::cout << "weak_count of weak_ptr after reset: " << weak.weak_count_use() << std::endl;

    {
        auto locked = weak.lock();
        if (locked) {
            std::cout << "Value via locked shared_ptr after reset: " << *locked << std::endl;
        } else {
            std::cout << "Object expired after reset." << std::endl;
        }
    }

    return 0;
}
