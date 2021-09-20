#pragma once

// #define PRINT_LOG 1

#ifdef PRINT_LOG
#include <iostream>
#endif

namespace lib
{

template<typename T, std::size_t Sz = 10>
struct custom_allocator {
    using value_type = T;

    template<typename U>
    struct rebind {
        using other = custom_allocator<U>;
    };

    custom_allocator() {
#ifdef PRINT_LOG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    }

    ~custom_allocator() {
#ifdef PRINT_LOG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        for(std::size_t i = 0; i < allocated_elements_count; ++i)
        {
            (allocated_memory_ptr + i)->~T();
        }
        if(allocated_memory_ptr)
        {
            std::free(allocated_memory_ptr);
        }
    }

    template<typename U> 
    custom_allocator(const custom_allocator<U>&) {
#ifdef PRINT_LOG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    }

    T *allocate(std::size_t n) {
#ifdef PRINT_LOG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        if((allocated_elements_count + n) > Sz)
            throw std::bad_alloc();
        if(!allocated_memory_ptr)
            allocated_memory_ptr = reinterpret_cast<T*>(std::malloc(Sz * sizeof(T)));
        if (!allocated_memory_ptr)
            throw std::bad_alloc();
        T* ptr = allocated_memory_ptr + allocated_elements_count;
        allocated_elements_count += n;
        return ptr;
    }

    void deallocate([[maybe_unused]] T *p, [[maybe_unused]] std::size_t n) {
#ifdef PRINT_LOG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        // std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
#ifdef PRINT_LOG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy([[maybe_unused]] T *p) {
#ifdef PRINT_LOG
        std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
        // p->~T();
    }

private:
    T* allocated_memory_ptr = nullptr;
    std::size_t allocated_elements_count = 0; 
};

}