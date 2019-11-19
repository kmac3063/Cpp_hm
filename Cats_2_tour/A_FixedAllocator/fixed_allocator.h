#pragma once
#include <vector>

template<typename Tp>
class FixedAllocator {
    PageAllocator page_allocator_;

    std::uint64_t page_size_;
    Tp* p = 0;
    std::vector<Tp*> free_p;

    bool first_call = true;

 public:
     explicit FixedAllocator(std::uint64_t page_size) :
        page_allocator_(page_size * sizeof(Tp)),
        page_size_(page_size) {}

    Tp* Allocate() {
        if (first_call) {
            first_call = false;
            p = static_cast<Tp*>(page_allocator_.Allocate());
            for (size_t i = 0; i < page_size_; i++)
                free_p.push_back(p + i);
        }

        if (free_p.empty()) {
            p = static_cast<Tp*>(page_allocator_.Allocate());
            for (size_t i = 0; i < page_size_; i++)
                free_p.push_back(p + i);
        }

        p = *(--free_p.end());
        free_p.erase(--free_p.end());
        return p;
    }

    void Deallocate(Tp* p) {
        free_p.push_back(p);
    }

    const PageAllocator& InnerAllocator() const noexcept {
        const PageAllocator& a = page_allocator_;
        return a;
    }
};
