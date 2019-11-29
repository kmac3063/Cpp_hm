#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <iostream>

#include "Test.hpp"

namespace smart_pointer {
    // `exception` class definition
class exception : std::exception {
    using base_class = std::exception;
    using base_class::base_class;
};

    // `SmartPointer` class declaration
    template<
        typename T,
        typename Allocator
    >
class SmartPointer {
    // don't remove this macro
    ENABLE_CLASS_TESTS;

 public:
    using value_type = T;

    explicit SmartPointer(value_type* p_ = nullptr) {
        if (p_ == nullptr)
            return;

        core = new Core(static_cast<void*>(p_), 1);
    }

    // copy constructor
    SmartPointer(const SmartPointer& sp) : core(sp.core) {
        if (core != nullptr)
            core->counter++;
    }

    // move constructor
    SmartPointer(SmartPointer&& sp) : core(std::move(sp.core)) {
        sp.core = nullptr;
    }

    // copy assigment
    SmartPointer& operator=(const SmartPointer& sp) {
        if (core != nullptr && --core->counter == 0) {
            delete core;
            core = nullptr;
        }
        core = sp.core;
        if (core != nullptr) {
            core->counter++;
        }
        return *this;
    }

    // move assigment
    SmartPointer& operator=(SmartPointer&& sp) {
        if (core != nullptr && --core->counter == 0) {
            delete core;
            core = nullptr;
        }

        core = std::move(sp.core);
        sp.core = nullptr;

        return *this;
    }

    //
    SmartPointer& operator=(value_type* p) {
        if (core != nullptr && --core->counter == 0) {
            delete core;
            core = nullptr;
        }

        if (p == nullptr)
            core = nullptr;
        else
            core = new Core(p, 1);

        return *this;
    }

    ~SmartPointer() {
        if (core != nullptr && --core->counter == 0)
            delete core;
    }

    // return reference to the object of class/type T
    // if SmartPointer contains nullptr throw `SmartPointer::exception`
    value_type& operator*() {
        if (core == nullptr)
            throw smart_pointer::exception();
        return *static_cast<value_type*>(core->p);
    }

    const value_type& operator*() const {
        if (core == nullptr)
            throw smart_pointer::exception();
        return *static_cast<value_type*>(core->p);
    }

    // return pointer to the object of class/type T
    value_type* operator->() const {
        if (core == nullptr)
            return nullptr;
        return static_cast<value_type*>(core->p);
    }

    value_type* get() const {
        if (core == nullptr)
            return nullptr;
        return static_cast<value_type*>(core->p);
    }

    // if pointer == nullptr => return false
    operator bool() const {
        return core != nullptr;
    }

    // if pointers points to the same address or both null => true
    template<typename U, typename AnotherAllocator>
    bool operator==(const SmartPointer<U, AnotherAllocator>& sp) const {
        return static_cast<void*>(get()) == static_cast<void*>(sp.get());
    }

    // if pointers points to the same address or both null => false
    template<typename U, typename AnotherAllocator>
    bool operator!=(const SmartPointer<U, AnotherAllocator>& sp) const {
        return !(*this == sp);
    }

    // if smart pointer contains non-nullptr => return count owners
    // if smart pointer contains nullptr => return 0
    std::size_t count_owners() const {
        if (core == nullptr)
            return 0;
        return core->counter;
    }

 private:
    class Core {
     public:
        Core(void* p_, size_t c) : p(p_), counter(c) {}

        ~Core() {
            Allocator al;
            al.deallocate(static_cast<value_type*>(p), 1);
        }
        void set(void* p_, size_t c) {
            p = p_;
            counter = c;
        }

        void* p;
        size_t counter = 0;
    };

    Core* core = nullptr;
};
}  // namespace smart_pointer
