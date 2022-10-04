## Requirements
 - Kernels shall be of size `m x n` and stored in row-order.
   - `m` is number of rows, `n` is number of columns.
   - This is the standard mathematical notation and also the standard way
     arrays are laid out in computer memory.
 - Kernel element access should be done with the variable names `m` and `n` with
   their meanings as given above.
   - Avoid using names such as `x` and `y` when working within kernel space.
 

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