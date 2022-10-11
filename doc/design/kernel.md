**NOTE: I am strongly considering removing all kernel classes and moving them into a
  simple math library as a 'matrix' class.**

## Requirements
 - Kernels shall be of size `m` x `n` and stored in row-order.
   - `m` is number of rows, `n` is number of columns.
   - This is the standard mathematical notation and also the standard way
     arrays are laid out in computer memory.
 - ~~Kernel element access should be done with the variable names `m` and `n` with
   their meanings as given above.~~
   - ~~Avoid using names such as `x` and `y` when working within kernel space.~~
   - *I am not sold on this requirement for notation. `m` and `n` represent the kernel/matrix
      size and not indices into the kernel/matrix. Should probably use `i` and `j` as the
      access indices as this is standard notation.* \
 - The section below lists the *operations* of the kernel/matrix classes. It would be nice
   to define many of these as *virtual* functions in `IKernel` but I am worried about performance
   associated with virtual function lookups in our algorithms. It appears the compilers are
   allowed to inline virtual functions if it knows the exact type it is working on (see
   [here](http://www.cs.technion.ac.il/users/yechiel/c++-faq/inline-virtuals.html)). However,
   probably not all compilers will make this optimization so we should have a `#ifdef/#ifndef`
   to enable non-virtual use of these functions.

 **Operations**
 - `kernel[i][j]` - Unchecked access to kernel elements.
   - The current implementation of this access will use an overload of the `[]` operator
     that returns, unfortunately, a `std::array` reference which can then be chained another
     `[]` access. This exposes our inner implementation details and should be remedied by a
     return a `Kernel_ref` class instead (or probably `Matrix_ref` since kernel will probably
     be moved to a matrix class). See Chapter 29 in *The C++ Programming Language* by Bjarne
     Stroustrup for an example design. As long as clients access the returned object by
     `[]` again and don't mess around with the returned object, we probably won't have too
     many problems until we get our reference class implemented.
 - `kernel.at(i,y)` - Checked access to kernel elements.
 - `kernel.row(i)` - Returns the kernel/matrix row at *i*.
   - This has the same inner implementation exposure as detailed for the `kernel[i][j]`
     operation and will be remedied once our reference class is in place.
 

## Design

![Kernel Class Hierarchy](diagram/kernel_class_hierarchy.png "Kernel Class Hierarchy")


## ToDo

 - Can we just consolidate all the kernel types into a single kernel that is
   stored as nested arrays (e.g. `vector<vector<float>>` or perhaps
   `array<array<float>>`)? This seems like it should provide the 
   multidimensional array performance gains like we see with `KernelFast`
   instead of the offset computation of a single array like in `Kernel`.
 - Can our processing functions just accept `IKernel` objects and call a
   method like `kernel->is_fast()` to determine if it can index into the
   member data's multidimensional array? It can just call a more optimized
   function to process if `true`.
   - Currently, there is a performance gain due to compiler optimizations for
     specifying the inner kernel for loop based on template members `M` and `N`.
     - Future note: If input data sizes are all the same, there could be a
       slight performance increase by templating the data for loops on their
       variables, though this will be less than the optimization seen on the
       kernel for loops (the outer data loops are not looped as much as the
       inner kernel loops, and the relative performance gains for the outer
       data loops will possibly decrease relative as kernel sizes increase).