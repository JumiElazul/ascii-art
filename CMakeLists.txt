cmake_minimum_required(VERSION 3.19)

project(ascii-art VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    "src/application.cpp"

    "src/argument_parser.cpp"
    "src/ascii_parser.cpp"
    "src/image.cpp"
)

set(HEADERS
    "include/application.h"

    "include/argument_parser.h"
    "include/ascii_parser.h"
    "include/image.h"
)

find_path(STB_INCLUDE_DIR "stb_image.h")
if(NOT STB_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find stb_image.h. Make sure stb is installed in vcpkg.")
endif()

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${STB_INCLUDE_DIR})

if (MSVC)
    target_compile_options(stb INTERFACE /W0)
else()
    target_compile_options(stb INTERFACE -w)
endif()


add_executable(ascii-art "src/main.cpp")
add_library(ascii-art-lib STATIC ${SOURCES} ${HEADERS})

target_include_directories(ascii-art-lib PUBLIC include)
target_link_libraries(ascii-art-lib PRIVATE stb)

find_package(boost_program_options REQUIRED CONFIG)
target_link_libraries(ascii-art-lib PRIVATE Boost::program_options)

target_link_libraries(ascii-art ascii-art-lib)
