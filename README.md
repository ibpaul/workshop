# Workshop
Tools for developing algorithms.

## Build and Run
The project uses CMake and can be compiled with normal CMake commands.

1. Run the *cmake* command.
```
cmake .
```

2. Run `cmake-gui .` to open the settings window and make necessary configurations.
 - Add `ZLIB_LIBRARY` with path to *<repo>/libs/zlib*.
 - Modify `ZLIB_INCLUDE_DIR` to point to *<repo>/libs/zlib*.
 - Modify `ZLIB_LIBRARY_DEBUG` to point to *<repo>/libs/zlib/Debug*.
 - Modify `ZLIB_LIBRARY_RELEASE` to point to *<repo>/libs/zlib/Release*.
 - Click the *Configure* button.

3. Rerun cmake configuration.
```
cmake .
```

4. Open the Visual Studio solution located at *<repo>/Workshop.sln*.

5. Add library link references to the *png* project.
  1. Right-click the *png* project and select *Properties...*.
  2. Expand the group *Configuration Properties -> Linker -> General*.
  3. For the setting *Additional Library Directories*, add a path to *<repo>/libs/zlib/Debug*.
  4. Expand the group *Configuratin Properties -> Linker -> Input*.
  5. For the setting *Additional Dependencies*, add *zlibd.lib*.

6. Build and run the *runner* project by right-clicking it and selecting *Debug -> Start New Instance*.
