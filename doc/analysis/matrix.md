# Matrix Support

*NOTE: The workshop and it's associated libraries was initially intended to have its own
 light-weight matrix library to a) minimize dependencies, and b) allow investigation in to
 possible optimization techniques for our algorithms. Cleaning up the existing matrix classes
 was showing that a large effort would be needed to make a satisfactory implementation and was
 distracting from other developments that could be done with the workshop and libraries.*

The workshop and associated libraries use the matrix classes from *Eigen*. This library provides
more general matrix classes suitable for mathematical operations (as opposed to specific graphical
rendering work). The matrices and associated functions from this library are also assumed to
be fairly performant.

Much of the analysis of the various libraries available were pulled from [this](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a)
StackOverflow post.


## Available Options

- *In-House Matrices*
  - Originally this was the development direction to reduce outside dependencies and investigate
    optimization techniques.
  - Would require development efforts and maintenance that would be better spent elsewhere.
  - Would always be limited in features and possible optimizations that already exist in other
    third-party libraries.
  - If desired and possible optimizations are not present in existing third-party libraries,
    it is probably more feasible to either modify the existing third-party library or to
    develop workarounds for the expected isolated instances where optimizations could be made
    that are not present in the library.
  - See previous design work in [Matrix - Overview](../design/matrix/overview.md) for details
    encountered in developing our in-house matrix classes.

- *Eigen*
  - "Clean, well designed API, fairly easy to use." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Seems to be well maintained with a vibrant community." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Low memory overhead. High performance." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Made for general linear algebra." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "All header library, no linking required." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))

- *Generic Graphics Toolkit (GMTL)*
  - "Simple API, specifically designed for graphics engines." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Doesn't include general purpose (MxN) matrices, matrix decomposition and solving, etc." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))

- *IMSL Numerical Libraries*
  - "Very complete numeric library." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Very, very fast (supposedly the fastest solver)." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Commerical, not inexpensive." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))

- *Numerical Template Toolbox (NT2)*
  - "Provides syntax similar to MATLAB." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Probably not as performant as Eigen." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))

- *LAPACK*
  - "Very stable, proven algorithms. Been around for a long time." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Many options for obscure mathematics." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))
  - "Probably not as performant as Eigen." ([src](https://stackoverflow.com/questions/1380371/what-are-the-most-widely-used-c-vector-matrix-math-linear-algebra-libraries-a))