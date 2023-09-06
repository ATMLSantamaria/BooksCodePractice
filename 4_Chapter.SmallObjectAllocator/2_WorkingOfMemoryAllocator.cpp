#include <cstddef>
// How does a memory allocator work? A memory allocator manages a pool of raw bytes and is able to
// allocate chunks of arbitrary size from that pool. The bookkeeping structure can be a simple control block
// having a structure like the following:

struct MemControlBlock
{
    size_t size_;
    bool available_;
};
// The memory managed by a MemControlBlock object lies right after it and has size_ bytes. After the
// chunk of memory, there is another MemControlBlock , and so on.

// For each allocation request, a linear search of memory blocks finds a suitable block for the requested size.
// Its size must be equal to or larger than the size requested. It is amazing just how many strategies for fitting
// requests with available blocks exist, and how oddly they perform. You can go for first fit, best fit, worst fit,
// or even a random fit. Interestingly, worst fit is better than best fit—how's that for an oxymoron?

// Each deallocation incurs, again, a linear search for figuring out the memory block that precedes the block
// being deallocated, and an adjustment of its size

// As you can see, this strategy is not terribly time efficient. However, the overhead in size is quite small—
// only one size_t plus a bool per memory block.

// If you store pointers to the previous and next MemControlBlock in each MemControlBlock , you can
// achieve constant-time deallocation. This is because a block that's freed can access the adjacent blocks
// directly and adjust them accordingly. The necessary memory control block structure is

struct MemConstrolBlock
{
    bool available_ ;
    MemControlBlock* prev_;
    MemControlBlock* next_;
};

// Still, allocations take linear time. There are many neat techniques for mitigating that, each fostering a
// different set of trade-offs. Interestingly, there's no perfect memory allocation strategy; each of them has a
// memory use trend that makes it perform worse than others.
// We don't need to optimize general allocators. Let's focus on specialized allocators—allocators that deal
// best with small objects.
