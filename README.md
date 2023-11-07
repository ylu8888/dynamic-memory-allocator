# dynamic-memory-allocator

##Created an allocator for the x86-64 architecture with the following features:

* Free lists segregated by size class, using first-fit policy within each size class.
  
* Immediate coalescing of large blocks on free with adjacent free blocks.
  
* Boundary tags to support efficient coalescing.
  
* Block splitting without creating splinters.
  
* Allocated blocks aligned to "double memory row" (16-byte) boundaries.
  
* Free lists maintained using last in first out (LIFO) discipline.
  
* Use of a prologue and epilogue to avoid edge cases at the end of the heap.
  
* "Wilderness preservation" heuristic, to avoid unnecessary growing of the heap.

After completing this project, I now have a better understanding of:

* The inner workings of a dynamic memory allocator
  
* Memory padding and alignment
  
* Structs and linked lists in C

* errno numbers in C
  
* Unit testing in C
  
