## Requirements

 - Only fill kernels with an odd number for its dimensions.
   - Simplifies creating and processing with kernels for images. 
   - More direct processing since the center kernel element is centered over the
     image pixel being computed.


## Design
 - Compute the gaussian out to 3 sigma.
   - This captures the majority of the curve.
   - Could be adjusted later.
 - Compute only the positive side of the curve and copy the elements to the
   other side.
   - The curve is symmetrical and it probably much faster to copy memory rather
     than use the gaussian function to compute.
 - How should we normalize the computed values?
   - The central element will be at ~0.4 with standard *sigma* and *mu* values.
   - Will the normalization depend on the size of the kernel?