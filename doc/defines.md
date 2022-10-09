# Defines
This page contains a collection of preprocessor defines the library and tools use. Most of
these are geared towards the library's development and should typically not be used by library
users.

 - `LTS_LOAD_GAUSSIAN_MEMCPY` - This enables code that does memory copy operations to fill
   out the majority of a kernel for the `load_gaussian` function. This would work on our built-in
   kernel objects because the function knew the memory layout of these objects. This method for
   loading gaussian weights into a kernel failed when implementing the `KernelEigen` class. This
   class uses the *Eigen* library's matrix object and does not have the same memory layout and
   thus would fail to load properly.
