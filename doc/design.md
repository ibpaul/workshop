# Workshop Design Document

 - [Images](design/images.md)
 - [Matrix](design/matrix/overview.md)
 - [Gaussian Kernel](design/gaussian_kernel.md)
 - [Process Functions](design/process_functions.md)
 - [Filter Factory](design/filter_factory.md)
 - __Tools__
   - [Play](tools/play.md)
   - [Filter](tools/filter.md)
   - [Zephyr Filter](tools/zephyr_filter.md)

## Definitions

 - *kernel* - The matrix which is loaded with specific values and then used
     in a process such as convolution on input data. Often refers to an empty
     matrix in code but normally means a matrix with a specific set of values.
 - *filter* - A combination of a kernel loaded with specific values and an
     associated processing method such as convolution.

## Development Notes

 - For code not compatible with the *Zephyr* platform, wrap the code in a
   preprocessor guard targeting the `__ZEPHYR__` define.
 - For *CMake* files, place guards around sections that are not compatible with
   *Zephyr* by testing if the `ZEPHYR_BASE` variable is set like
   `if (NOT DEFINED ZEPHYR_BASE)`.

## ToDo
 - Change namespace `filter` to `kernel`?
   - Most of our objects in here are kernels, but it also contains the operations
     used on kernel objects, so the keeping the namespace `filter` the same
     is logically consistent.
