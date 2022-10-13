*Workshop* and its associated libraries now use the matrix classes found in the *Eigen* library.
There is a small `SimpleMatrix` that is provided by workshop for performance time comparisons
with the Eigen library matrices.

Old development design notes for the in-house matrix classes may be found [here](deprecated/overview.md).


## `SimpleMatrix`

 - Static (compile-time) sized `m` x `n` 2-dimensional matrix.
 - Access elements with `m(i,j)`.
 - Contains `rows()` and `cols()` for `m` x `n` queries.