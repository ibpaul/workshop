# Play Tool
The *play* tool is a simple tool for playing or displaying media files.

## Design
 - The tool will be provided a media filename to play/display as a command-line argument. The
   tool will determine the type of file by inspecting the filename's extension and display/play
   accordingly.
 - Image files will simply have the image displayed. \
   `play data/peppers.png`
 - Sound files will simply have the sound played. \
   `play data/band.wav`


## Specifications
 - Implement sound file playing using the Simple Fast Media Library (SFML).
   - *Allows us to initially have broad system support for sound files (Windows, Linux, MacOS).*
   - *Can add direct Window API access to play sound files later.*
