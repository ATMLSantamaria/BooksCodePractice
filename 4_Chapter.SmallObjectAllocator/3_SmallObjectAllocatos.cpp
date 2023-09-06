// The small-object allocator described in this chapter sports a four-layered structure
// The upper layers use functionality provided by the lower layers. At the bottom is a Chunk type.

// 1 Each object of type Chunk contains and manages a chunk of memory consisting of an integral number of fixed-
// size blocks. Chunk contains logic that allows you to allocate and deallocate memory blocks. When there
// are no more blocks available in the chunk, the allocation function fails by returning zero.

// 2 FixedAllocator object uses Chunk as a building block. FixedAllocator 's primary purpose is to satisfy memory requests that go beyond a
// Chunk 's capacity. FixedAllocator does this by aggregating an array of Chunk s. Whenever a request
// for memory comes and all existing Chunk s are occupied, FixedAllocator creates a new Chunk and
// appends it to the array. Then it satisfies the request by forwarding the request to that new Chunk .

// 3 SmallObjAllocator provides general allocation and deallocation functions. A SmallObjAllocator
// holds several FixedAllocator objects, each specialized for allocating objects of one size. Depending
// on the number of bytes requested, SmallObjAllocator dispatches memory allocation requests to one
// of its FixedAllocator s or to the default ::operator new if the size requested is too large.

// 4 SmallObject wraps FixedAllocator to offer encapsulated allocation services for C++
// classes. SmallObject overloads operator new and operator delete and passes them to a
// SmallObjAllocator object. This way, you make your objects benefit from specialized allocation by
// simply deriving them from SmallObject.

