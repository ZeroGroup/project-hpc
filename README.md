# project-hpc
A project for High Performance Calculation

## Directory Structure
As follows

    /                       - working copy of repository (name irrelevant).
      |- bin/               - installed executables. Content .gitignored
      |- build/             - cmake output files. Content .gitignored
      |- doc/               - documentaation, notes.
      |- include/           - headers for use with generated liraries in other projects
      |- lib/               - installed libraries. Content .gitignored
      `- hpc/               - project sources root
         |- CMakeLists.txt
         `- component_name/ - root of specific component sources
            |- CMakeLists.txt
            |- src/         - sources
            |  |- include/  - added to include dir. See Include Directories
            |  |- cpp/      - C++ source files.
            |  `- cuda/     - CUDA source files.
            `- tests/       - for 75% sure Google Test sources.

Jump to [Include Directories](#include-directories) section.

## Compilation and Execution
In this section...

  * Note, that installation prefix is fixed in hpc/CMakeLists.txt and points to root repository, which makes easy to just run ```make install``` and search for various binaries in single ```bin``` directory. TODO: make it parametrized with DEBUG/RELEASE build selection.

### Requirements
1. CMake Version >= 2.8
2. CUDA Compute Capability >= 3.0 (kepler)

### Compilation Steps<a name="compilation-steps"></a>
1. cd build
2. cmake ../hpc
3. make
4. make install

  Optionally replace steps 1 and 2 by <br />
    ```$ cmake -Bbuild -Hhpc```

### Execution Steps
1. navigate to bin directory
2. run binaries of your choice

## Coding standard and CMake configuration
In this section...
### Include Directories
in component, src/include directory should have following structure

    src/
      `- include/
         `- <project name>/     - this is "hpc" for now.
            `- <component_name>/
               `- <file_name>.hpp

so when you include file A.hpp from component B in component C, you write

    #include <hpc/B/A.hpp>

regardless of your current position in project. Even if you create file Utils.hpp in component X, you will never collide with someone else who use this name in component Y.

Combined with namespaces makes freedom for developer when it comes to name his files.

Directory src of component itself can contain private headers that are not to be exposed to other components. I suggest create directory "private" there and use simply

    #include "private/HeaderName.hpp"

in C++ source files and other private headers, note:

  * No public header is allowed to include private symbols!

### FAQ
1.
  **Q:** I got "You should not call cmake in-source..." error, why?

  **A:** Becouse this will create heavily polluted working copy, which may result in accidentaly adding binaries to version control, small kittens horrible death or even total extinciton of *Ailuropoda melanoleuca* species. The solution is to re-read and understand [Compilation Steps](#compilation-steps) subsection of this file.
