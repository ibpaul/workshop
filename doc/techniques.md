# Techniques
This page contains a collection of useful development techniques.

## Loop Unrolling
The compiler at times can make a space-time tradeoff with regard to for loops called
[loop unrolling](https://en.wikipedia.org/wiki/Loop_unrolling). This led to performance gains
we originally saw with the `convolute` function when we operated on a, now defunct, `MatrixFast<T, M, N>`
object. At compile-time, we were able to inject the matrix's known size into the inner kernel
loop's condition check and the compiler would make the *loop unrolling* optimization.
