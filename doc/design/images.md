# Images

## Requirements

- Images sizes/shape shall be specified by their `height` x `width` x `channels`
  and all references should maintain this ordering.
  - Example, the method for processing image data should have its signature
    as `process(data*, height, width, channels)`.
