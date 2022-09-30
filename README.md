# Workshop
Tools for developing algorithms.

## Quick Build and Run
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

## Release Build and Run
The default build environment creates *debug* executables which will not run as
fast as full *release* builds, so it is import when running performance timing tests
to compile as *release*.

### Visual Studio 
The steps are the same as in *Quick Build and Run* but with the adjustments below.

- With *Visual Studio* open, select the option *Release* from toolbar drop-down.

- The associated linker options will be as below instead.
  - `<repo_full_path>/build/libs/zlib/Release`
  - `zlib.lib`

- When you run the program with performance time testing, make sure you run the
  project without the attached debugger as this typically slows the program down
  by up to 5x. To do this, right-click on the *filter* project and select
  *Debug -> Start Without Debugging*.

### CLion
The steps are the same as in *Quick Build and Run* but with the adjustments below.

- Create a *release* build configuration when you open *CLion* by going to the
  menu *File -> Settings -> Build, Execution, Deployment -> CMake*. For the list
  of *Profiles* click the *plus (+)* button, and it should add the *Release* build
  profile automatically.

- On the main menu, from the drop-down menu on the toolbar, make sure the option *Release*
  is selected.

- You may need to clean up existing files because *CLion* will sometimes use previous
  build intermediates if previously compiled in *debug*. If needed, go to *Build -> Clean*.