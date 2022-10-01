// Single collection of flags to coordinate various optimization attempts.

#ifndef LTS_OPTIMIZE_FLAGS_H
#define LTS_OPTIMIZE_FLAGS_H

// [OPTIMIZE NOTES]
//  - Only enable either OPTIMIZE_1, OPTIMIZE_2 or OPTIMIZE_3. Do not enable multiple ones!

#define OPTIMIZE_1 0
// OPTIMIZE_1 changes how the kernel weights are accessed in the filter's for loops.
// Instead of accessing them like below each time in the for loop...
//
//     weights[y*num_cols + x]
//
// ...we access them like below...
//
//     *weights_ptr++
//
// This optimization relies on the nested for loops accessing the kernel weights sequentially
// and thus avoids the multiplication during each loop.
//
// This does appear to give a performance increase but is still slower than the implementation
// in Gaussian_v1 where the elements are stored in a multidimensional array and accessed like
// the code below...
//
//     weights[y][x]
//

#define OPTIMIZE_2 0
// OPTIMIZE_2 is not expected to provide any noticeable performance increase.
//
// It eliminates a variable from the inner loops and instead dereferences the pointer access
// as implemented in OPTIMIZE_1.

#define OPTIMIZE_3 1
// OPTIMIZE_3 converts the kernel weights to a multidimensional array.
//
// This optimization configuration is the setup as employed in Gaussian_v1 and provides the
// same performance level for Gaussian_v2. This is the fast optimization level currently.


#endif //LTS_OPTIMIZE_FLAGS_H
