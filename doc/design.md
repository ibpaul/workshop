# Workshop Design Document

 - [Images](design/images.md)
 - [Kernel](design/kernel.md)
 - [Gaussian Kernel](design/gaussian_kernel.md)
 - [Filter Factory](design/filter_factory.md)

## Definitions

 - *kernel* - The matrix which is loaded with specific values and then used
     in a process such as convolution on input data. Often refers to an empty
     matrix in code but normally means a matrix with a specific set of values.
 - *filter* - A combination of a kernel loaded with specific values and an
     associated processing method such as convolution.

## ToDo
 - Change namespace `filter` to `kernel`?
   - Most of our objects in here are kernels, but it also contains the operations
     used on kernel objects, so the keeping the namespace `filter` the same
     is logically consistent.
