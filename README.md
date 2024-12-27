# ascii-art

ascii-art is a command line tool to create ascii-art from an image file and output it to the console, and to a .txt file.
Supports image files of any type that are opened using the stb_image library.

## Dependencies
- [stb](https://github.com/nothings/stb)
- [boost-program-options](https://github.com/boostorg/program_options)
- [vckpg](https://vcpkg.io/en/)

## Installation
The project uses CMake to build, with a CMakePresets.json file to tune different build configurations for platforms.
Vcpkg is required to install the dependencies.  Or you can grab a prebuilt binary from the releases section of the repository.

To build and install from source:
1. Add the VCPKG_ROOT environment variable to the path of the vcpkg directory.
2. Clone the repository
3. Run cmake --preset <preset> to build the project. The presets are:
    windows-x64-debug
    windows-x64-release
    linux-debug
    linux-release
    macos-debug (untested currently)
4. Run cmake --build <path_to_build> to build the project. (by default, the path is out/build/<preset>)
5. Finally, to install globally run cmake --install <path_to_build> --prefix <path_to_install>

## Usage
The tool can be used by running the ascii-art executable with the following options:
- help,H:   Produces a help message
- input,I:  Name of input files to process into ascii
- output,O: Name of output file to write to
- width,W:  Max width in characters of the output ascii
- ramp,R:   Ramp to use for ascii conversion, 0 for simple, 1 for complex
