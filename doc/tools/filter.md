# Filter Tool
The *fitler* tool is a command-line utility for running and evaluating algorithms.

A typical run of the *filter* tool from the command-line looks like this: \
```filter --type gaussian{3,3} data/peppers.png output.png```

This command will construct a 3x3 filter kernel loaded with gaussian (blur) weights,
process the file *data/peppers.png* through this filter, and save the output file
to *output.png*.

The *filter* tool also provides the ability to perform timing of the filter run time.
For example: \
\
```filter --test=1 --type gaussian{3,3} data/peppers.png output.png```

This performs the same operations as before but will display timing results such
as *mean time* and *jitter*.

Here, *jitter* will be meaningless because we only specified to perform one iteration
of the filter. To run 100 iterations, change the value for the `--test` parameter
like thus: \
\
```filter --test=100 --type gaussian{3,3} data/peppers.png output.png```

The following section provide details on the various configuration options available
for the *filter* tool.

## Filter Types
Filter types are specified with the `--type` flag, followed by the name of the
filter type to run along with adjustable parameters.

__Available Filter Types__
 - `gaussian`

The first two filter type parameters specified between the brackets `{` and `}`
specify the `m` x `n` size of the kernel to use. We can specify a `5` x `5` kernel
like thus: \
\
```--type gaussian{5,5}```

Kernel sizes should be odd numbers and they don't necessarily have to be square
(having the same value for both `m` and `n`).

The *filter* tool contains a list of commonly used kernel sizes, which when specified
from the command-line, allow the tool to run more optimized code. You can disable
this feature by specifying the `nofast` option filter parameter like show below. \
\
```--type gaussian{5,5,nofast}```

This list of optimized kernel sizes are listed below.

__Optimized Kernel Sizes__
 - `3` x `3`
 - `5` x `5`
 - `7` x `7`
 - `9` x `9`
 - `11` x `11`

Sorry if your favorite kernel size is not included in the list of optimized sizes.
This is only specific to the *filter* tool. If you include the kernel library code
in your project, you can get this optimization by creating your own templated
kernel class, say by using the `Eigen::Matrix<float, 21, 21>` in your code for your
favorite `21` x `21` kernel size.

### Built-In Matrix
Instead of using the matrices provided by the [*Eigen library*](https://eigen.tuxfamily.org/index.php?title=Main_Page),
you can use the small build-in matrix `SimpleMatrix`. This is useful for performing
timing comparisons with the Eigen library and adjusting your compiler's optimization
settings. Note that the `SimpleMatrix` is only available for the provided list of *Optimized
Kernel Sizes* above. \
\
`--type gaussian{5,5,simple}`


## Performance Testing
You enable performance testing by configuring the `--test` flag. You provide
parameters to this flag to toggle how to conduct the test.

The first parameter set by this flag is the number of iterations to perform the
test over. To run 200 iterations of the filter, specify this like: \
\
`--test=200`

Optionally, you can have the performance testing run on multiple threads to
evaluate performance of the filter runs as the number of threads running. For
example, you can run 200 iterations on 2 threads each like below (a total of 2 x 200 = 400
iterations are performed). \
\
`--test=200,2`

This provides you the ability to run twice as many tests in almost half the amount
of time. Notice in the printed tests results, the *mean time* for each iteration
is pretty much the same. Increasing the number of threads used for the performance
testing will not make the individual filter iterations any faster, just reduce
the total time it takes to perform the tests.

As you increase the number of threads used for testing, you will probably see the
*mean time* of each filter iteration increase. This is caused by the overhead
required by the system to run with all these threads. This can be useful for
seeing how system performance is affected by an increased number of threads
running at the same time.


## Input Data
Input data is specified by the first positional parameter, like `data/peppers.png`
earlier.

The tool only supports reading *PNG* files.

Alternatively, you can specify a *test pattern* instead of a file. The *filter*
tool will load the test pattern in memory and perform the filtering. You must
specify the image size when using the built-in test patterns. For example, you
can run the filter on an 512 x 512 image with just vertical lines by specifying the input
like `vertical-lines{512,512}`.

__Available Test Patterns__
 - `vertical-lines`
 - `horizontal-lines`

## Output File
The output file is optional and specifies where to save the processed file. This
must follow the input data parameter.


## Filter Multi-Threading
The filter processing can be flagged to run in multi-threaded mode. This is different from
the threading provided during testing, because now the data processing is using multiple
threads to process the data. You can flag multi-threaded mode with a flag option like: \
\
`--threads=2`

This flag signals to use 2 threads to process the data.

Note that some configurations of filter types and kernel sizes may not support multi-threading
and the program will respond with an error.