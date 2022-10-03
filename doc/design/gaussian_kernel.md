## Requirements

 - Only fill kernels with an odd number for its dimensions.
   - Simplifies creating and processing with kernels for images. 
   - More direct processing since the center kernel element is centered over the
     image pixel being computed.


## Design
 - Compute the gaussian out to 3 sigma.
   - This captures the majority of the curve.
   - Could be adjusted later.
 - Compute only the positive sides of the curve and copy the elements to the
   other sides.
   - The curve is symmetrical and it probably much faster to copy memory rather
     than use the gaussian function to compute.
 - How should we normalize the computed values?
   - The central element will be at ~0.4 with standard *sigma* and *mu* values.
   - Will the normalization depend on the size of the kernel?
 - Compute normal/gaussian pdf at each pixel's center
   - This means that at the ends, we are not calculating at the 3 sigma bound
     exactly. Since the 3 sigma bound is in the middle of an end pixel, it
     could be considered that the normal pdf curve extends further to the edge
     such as to 3.05 or so depending on the size of the kernel.
 - The pixels are computed by multiplying the value of the normal pdf at the
   pixel's x, y location.
 - Pixel values are calculated by row, starting at the middle of the row and
   then.
 - The current implementation is darkening the image. The kernel needs to be
   normalized (i.e. the area under the kernel's normal curves should sum to 1.0).