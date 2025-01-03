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

set(DEBUG_SOURCES_HEADERS
    "src/ascii_debug.cpp"
    "include/ascii_debug.h"
)

set(Boost_USE_STATIC_LIBS ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

find_path(STB_INCLUDE_DIR "stb_image.h")
if(NOT STB_INCLUDE_DIR)
    message(FATAL_ERROR "Could not find stb_image.h. Make sure stb is installed in vcpkg.")
endif()

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${STB_INCLUDE_DIR})

if(MSVC)
    target_compile_options(stb INTERFACE /W0)
else()
    target_compile_options(stb INTERFACE -w)
endif()

add_executable(ascii-art "src/main.cpp")
add_library(ascii-art-lib STATIC ${SOURCES} ${HEADERS} $<$<CONFIG:Debug>:${DEBUG_SOURCES_HEADERS}>)

install(TARGETS ascii-art RUNTIME DESTINATION bin)

target_include_directories(ascii-art-lib PUBLIC include)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(fmt CONFIG REQUIRED)

target_compile_definitions(ascii-art-lib PUBLIC
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:Release>:RELEASE>
)

target_link_libraries(ascii-art-lib PRIVATE
    Boost::program_options
    fmt::fmt
    stb
)

target_link_libraries(ascii-art ascii-art-lib)
