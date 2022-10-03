## Description
Specific filter types and configurations are specified by a formatted string.
The `FilterFactory` parses these strings and returns an appropriately constructed
`Filter` object.

## Requirements
 - Parse filter type/config from strings formatted like `"gaussian{11,11}"`.
   - The first part specifies the filter family type, in this case a *gaussian*
     filter kernel, sometimes also called a *blur* filter.
   - Specific implementations of the filter family may be specified like
     `"gaussian_v3{11,11}"`.
     - This specific implementation is a version of the *gaussian* filter that
       was developed.
     - If a specific implementation is not specified (e.g. `"gaussian{11,11}"`),
       then the factory will use the most appropriate specific implementation
       available, typically the latest version.
       - *Note: Selection is currently set in file `filter/gaussian.h`.*
   - Parameters for constructing the filter kernel directly follow the name and
     are enclosed in brackets `{` and `}`.
     - For 2-dimensional filters (the ones currently being developed for image
       processing, the first two values indicate the kernel's `MxN` size).
     - Future work for 1- or 3- dimensional filter kernels will be adjusted for
       the size specification.
       - 1-dimensional size: `"gaussian{11}"`
       - 3-dimensional size: `"gaussian{11,11,11}`
     - All size parameters for a specific kernel instantiation must include all
       sizing parameters.
       - i.e. there will NOT be any shortcut method for specifying a square
         2-dimensional kernel like `"gaussian{11}"`. It must be fully specified
         like `"gaussain{11,11}"`.
 - Our implementation contains both a *generic* kernel called `Kernel` and also
   a faster operating kernel called `KernelFast`.
   - The `KernelFactory` should create a `KernelFast` if possible and fall back
     on creating a generic `Kernel` if it is unable to create the fast version.
     - `KernelFast` is based on class templates and limits our general `KernelFactory`
       to a set of well-used kernel sizes.
       - The C++ template mechanism requires machine code generation for each
         template size of `KernelFast` used within the code and cannot dynamically
         create these kernel objects at run-time. Thus, we limit `KernelFast` to
         the well-used set of square kernels from size `3x3` to `11x11`. This may
         be adjusted and any future code that needs a specific instantiation of
         `KernelFast` may still do so in their own code (e.g. they are still free
         to create a `KernelFast` of size `23x45` and still receive its performance
         gains).
       - The list of available well-used kernel sizes may be adjusted in the future.
         Be aware that increasing this list may lead to necessary generated
         machine code bloat.
   - Both the generic `Kernel` and that fast `KernelFast` classes subclass the
     abstract `IKernel`.
     - This subclass allows general, non-performance critical code (such as loading
       the kernel weights) to be general and only operate on the `IKernel` interface.
     - Performance critical code (e.g. function `convolute`) should be called with
       the specific `KernelFast` object. Otherwise, the more general `convolute`
       overload will operate on the general `IKernel` interface.
       - The `FilterFactory` must take care that the faster `convolute` function is
         called if it is able to generate a `KernelFast` object.