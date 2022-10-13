# Lessons Learned
This page captures lessons learned during the development of *workshop* and its libraries.

 - Avoid defining new *matrix*, *vector*, and similar classes.
   - *Maybe a case can be made if the library should minimize external dependencies that it
     can be justified a library needs its own *matrix* and *vector* classes, but this should
     first be determined to be a hard requirement first. Consider,...*
     - *There are many stable and well-known existing matrix libraries, and chances are that
        a user of the library may be familiar with this library. Creating a new matrix library
        will require the user to learn yet another matrix class type.*
   - *The process of designing and creating a matrix data type is instructive and introduces
     one to many of the programming language's available features.*
   - *Matrices and vector classes should probably never be part of a virtual class hierarchy.
     It is impossible to get anywhere close to acceptable performance if element access
     functions must traverse through a vtable lookup every time an element is to be accessed.*
     - *Instead of trying to achieve "run-time polymorphism" through virtual class inheritance,
       there seems to be much to be gained with code reuse without lose of performance if
       "compile-time polymorphism" is attempted instead. For example, instead of attempting
       to write a generic function with a top-level matrix interface in a class hierarchy
       like below,...*
       ```cpp
       void compute(IVector* v) {
           for (auto i = 0; i < v.length(); ++i)
               cout << v[i] << endl;
       }
       ```
       *This will surely run into performance problems due to virtual functions and vtable
       traversals, especially if `compute` is called often. Instead, try templating and count
       on the compiler to check if the `length()` or `operator[]`
       features are available on the provided type. (Note: This has not been evaluated as
       workable but is considered the next step in current development for minimizing code
       working with different specific matrices and vector types.)*
       ```cpp
       template<typename V>
       void compute(V* v) {
           for (auto i = 0; i < v.length(); ++i)
               cout << v[i] << endl;
       }
       ```
