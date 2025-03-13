cmake_minimum_required(VERSION 3.0)

set(CMAKE_CUDA_COMPILER /usr/local/cuda-12.6/bin/nvcc)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CUDA_USE_RESPONSE_FILE_FOR_INCLUDES 0)
set(CMAKE_CUDA_USE_RESPONSE_FILE_FOR_LIBRARIES 0)
set(CMAKE_CUDA_USE_RESPONSE_FILE_FOR_OBJECTS 0)

project(VectorizedBatchPIR LANGUAGES C CXX CUDA)

# Set flags
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_CUDA_ARCHITECTURES 89)

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories(header)
set(CMAKE_CUDA_USE_RESPONSE_FILE OFF)

# Set the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Get all source files under src
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h" "src/*.cu")

# Create executable target and add source files
add_executable(vectorized_batch_pir ${SOURCES})

# Set include directories
target_include_directories(vectorized_batch_pir PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# vcpkg support
include(/home/runz/tools/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_TOOLCHAIN_FILE /home/runz/tools/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Set C++ standard
set_target_properties(vectorized_batch_pir PROPERTIES CXX_STANDARD 17)

# Add seal and troy library
find_package(SEAL 4.1 REQUIRED)

set(TROY_LIB "/home/runz/temp/troy")
include_directories(${TROY_LIB}/include)
link_directories(${TROY_LIB}/lib)

find_library(TROY_PATH troy "/home/runz/temp/troy/lib")

target_link_libraries(vectorized_batch_pir SEAL::seal ${TROY_PATH})
