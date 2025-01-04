# ascii-art

ascii-art is a command line tool to create ascii-art from an image file and output it to the console, and to a .txt file.  
Supports image files of any type that are opened using the stb_image library.

## Dependencies
- [vckpg](https://vcpkg.io/en/)
- [stb](https://github.com/nothings/stb)
- [boost-program-options](https://github.com/boostorg/program_options)
- [fmt](https://github.com/fmtlib/fmt)

## Installation
The project uses CMake to build, with a `CMakePresets.json` file to tune different build configurations for platforms.  
Vcpkg is required to install the dependencies, or you can grab a prebuilt binary from the releases section of the repository.

To build and install from source:

1. Add the `VCPKG_ROOT` environment variable to the path of the vcpkg directory.  
2. Clone the repository  
3. Run `cmake --preset <preset>` to build the project. The presets are:  
   - `windows-debug`  (x64)
   - `windows-release`  (x64)
   - `linux-debug`  
   - `linux-release`  
   - `macos-debug` (untested currently)

4. Run `cmake --build <path_to_build>` to build the project. (by default, the path is `out/build/<preset>`)  
5. Finally, to install globally run `cmake --install <path_to_build> --prefix <path_to_install>`

## Usage
The tool can be used by running the ascii-art executable with the following options:

- `help,h`: Produce help message  
- `input,i`: Name of input files to process into ascii (flag is optional, anything without a flag is considered an input file)
- `output,O`: Name of output file to write to  
- `width,W`: Width in characters of the output ascii. If height is not set, aspect ratio will be maintained  
- `height,H`: Height in characters of the output ascii. If width is not set, aspect ratio will be maintained  
- `ramp,R`: When set, use a more complicated ramp for ascii calculation  
- `invert,I`: Inverts the ascii-calculation so that dark pixels are the lightest and vice versa  
- `flip-y,Y`: Flips the image vertically  
- `flip-x,X`: Flips the image horizontally  
- `color,C`: Retains the color and produces a colored ascii image  
- `disable-console,D`: Disables the console output for ascii art and only prints to file  
- `char-aspect-ratio,A`: Aspect ratio of how much taller than wide the terminal characters are for ascii conversion. Given a value of 2.0, for every 2 characters wide, the character is 1 character tall. This will not take effect when width and height are both set
