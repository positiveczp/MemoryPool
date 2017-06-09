# MemoryPool

This is a template class implementation of a memory pool allocator that is very simple to use and extremely fast with minimal overhead for each allocation/deallocation.

## What is a Memory Pool

You would normally use malloc or new for dynamic memory management in C/C++. These functions are rather slow and have some memory overhead attached to them. This is fine if you make a few calls and ask for large chunks of memory, but if you need to store many small objects, the time and memory overhead may be unacceptable for high performance programs. This is where a memory pool comes in. A memory pool allocates memory in big chunks and splits the memory into smaller pieces. Every time you request memory, one of these small chunks is returned instead making a call to the OS or the heap allocator. You can only use a memory pool if you know the size of the objects beforehand, but if you do, a memory pool has a lot of advantages:

* It is substantially faster than malloc or new
* There is almost no memory overhead since the size of each object is known beforehand (i.e. no need to store allocation metadata)
* There is little to no memory fragmentation
* You do not need to free object one by one. The allocator will free all the memory it allocated once its destructor is called. Note that this only works if the objects have a default destructor.

A memory pool has just a few disadvantages:

* Objects have a fixed size which must be known beforehand. This is usually not a problem and mostly the case if you need to allocate them in a bunch
* You may need to fine tune them for your specific application. This is made very easy with the use of template classes.

## When to Use

You should use a memory pool when you need to allocate many objects of the same size. This is usually the case when you implement common data structures like linked lists, binary search trees, hash tables with chaining and so on. Using a memory pool in these cases will increase performance by several folds and reduce wasted memory substantially.
