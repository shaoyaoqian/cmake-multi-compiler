cmake_minimum_required(VERSION 3.27)

option(ENABLE_FEATURE "Enable feature" ON)


# set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_COMPILER /home/kokkos/spack/opt/spack/linux-ubuntu20.04-icelake/gcc-11.4.0/gcc-13.2.0-4hec755h2hicwphybea4n37xb5hue7gg/bin/g++)
set(CMAKE_C_COMPILER /home/kokkos/spack/opt/spack/linux-ubuntu20.04-icelake/gcc-11.4.0/gcc-13.2.0-4hec755h2hicwphybea4n37xb5hue7gg/bin/gcc)
add_subdirectory(your_library)
project(ProjectName)
add_executable(haha main.cpp)

target_link_libraries(haha PRIVATE your_library)


