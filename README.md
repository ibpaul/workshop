# Workshop
Tools for developing algorithms.

## Build and Run
The project can be built and run with the following environments.

 - Visual Studio 2022
 - CLion 2022.2.3

### Visual Studio

1. Run the *cmake* command to generate project files.
```
cmake .
```

2. Open the generated Visual Studio solution located at *\<repo\>/Workshop.sln*.

3. Add library link references to the *png* project.
    - Right-click the *png* project and select *Properties...*.
    - Expand the group *Configuration Properties -> Linker -> General*. 
    - For the setting *Additional Library Directories*, add a path to *\<repo\>/libs/zlib/Debug*. 
    - Expand the group *Configuration Properties -> Linker -> Input*. 
    - For the setting *Additional Dependencies*, add *zlibd.lib*.

4. Build and run the *runner* project by right-clicking it and selecting *Debug -> Start New Instance*.


### CLion

1. Open the project top-level folder in *CLion*.

2. From the *Configuration* drop-down, select *runner*.

3. Click the *Run* button.
