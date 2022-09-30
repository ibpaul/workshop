# Workshop
Tools for developing algorithms.

## Build and Run
The project can be built and run with the following environments.

 - Windows - Visual Studio 2022
 - Windows - CLion 2022.2.3
 - Ubuntu 22.04 LTS

### Visual Studio

1. Create a directory inside the project called *build* and make the Visual Studio project files in that directory.
```
mkdir build
cd build
cmake ..
```

2. Open the generated Visual Studio solution located at */bulid/Workshop.sln*.

3. Add library link references to the *png* project.
    - Right-click the *png* project and select *Properties...*.
    - Expand the group *Configuration Properties -> Linker -> General*. 
    - For the setting *Additional Library Directories*, add a path to *\<repo_full_path\>/build/libs/zlib/Debug*. 
    - Expand the group *Configuration Properties -> Linker -> Input*. 
    - For the setting *Additional Dependencies*, add *zlibd.lib*.

4. Build and run the *filter* project by right-clicking it and selecting *Debug -> Start New Instance*.


### CLion

1. Open the project top-level folder in *CLion*.

2. From the *Configuration* drop-down, select *filter*.

3. Edit program arguments by selecting *Edit Configurations* from the drop-down. Add the
   arguments to the *Program arguments* field:
```
--type gaussian{10,10} data/peppers.png output.png
```

4. Save settings and click the *Run* button.


### Ubuntu

1. Install tools and libraries.
```
sudo apt install cmake build-essential zlib1g-dev libx11-dev
```

2. Run the cmake commands to build.
```
mkdir build
cd build
cmake ..
cmake --build .
```

3. Change to the top-level directory and run the program.
```
cd ..
build/tools/filter/filter --type=gaussian{10,10} data/peppers.png output.png
```

