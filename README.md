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

## Picking BlockSize
Picking the correct BlockSize is essential for good performance. I suggest you pick a power of two, which may decrease memory fragmentation depending on your system. Also, make sure that BlockSize is at least several hundred times larger than the size of T for maximum performance. The idea is, the greater the BlockSize, the less calls to malloc the library will make. However, picking a size too big might increase memory usage unnecessarily and actually decrease the performance because malloc may need to make many system calls.

## About the Code

Here are a few important points that you should know about the code:

* This code handles alignment for the objects automatically, which is necessary for high performance memory access and may even be required on certain processors. However, it assumes the memory returned by operator new is "aligned enough" to store a pointer. This assumption was not necessary, but since it is reasonable enough, I decided to remove two lines of code. I am not sure if this is required by the standard, but all C code using malloc would crash (or run extremely slowly) if this was not the case.

* The allocator does not free any memory until it is destructed (though it does re-use the memory that you deallocate). This is fine if you only allocate objects, or if you deallocate and re-allocate objects equally often. This is only a problem if you have peaks of high memory usage and you expect the memory to be freed during low memory periods. This was a design choice to substantially improve the performance, and under most cases you do not need to worry about this. It is good to keep this mind for projects that require special handling of the memory though.

## References
* http://blog.csdn.net/pi9nc/article/details/11214473
* http://blog.csdn.net/jcjc918/article/details/44997089
* http://www.cnblogs.com/wpcockroach/archive/2012/05/10/2493564.html
* http://blog.csdn.net/justaipanda/article/details/7790355
*  http://www.cplusplus.com/reference/memory/allocator/
*  http://www.cplusplus.com/reference/memory/allocator_traits/
* http://blog.csdn.net/zhangxinrun/article/details/5940019
* http://www.cnblogs.com/BeyondTechnology/archive/2010/09/19/1831293.html




