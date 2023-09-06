// 1 The default allocator is notoriously slow. A possible reason is that it is usually
// implemented as a thin wrapper around the C heap allocator ( malloc / realloc / free ). The C heap
// allocator is not focused on optimizing small chunk allocations. C programs usually make ordered,
// conservative use of dynamic memory. They don't naturally foster idioms and techniques that lead to
// numerous allocations and deallocations of small chunks of memory.

// 2 The genericity of the default C++ allocator makes it very space inefficient for
// small objects. The default allocator manages a pool of memory, and such management often requires some
// extra memory. Usually, the bookkeeping memory amounts to a few extra bytes (4 to 32) for each block
// allocated with new . If you allocate 1024-byte blocks, the per-block space overhead is insignificant (0.4%
// to 3%). If you allocate 8-byte objects, the per-object overhead becomes 50% to 400%, a figure big enough
// to make you worry if you allocate many such small objects.

