cmake_minimum_required(VERSION 3.27)

# 设置 C++ 标准版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CUDA_ARCHITECTURES 89)

project(YourLibraryProject LANGUAGES CXX CUDA)


# 指定输出的库名称
set(KOKKOS_LIB_NAME your_library)

# 指定源文件
set(SOURCE_FILES example.cpp)

# 设置头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 生成共享库
add_library(${KOKKOS_LIB_NAME} SHARED ${SOURCE_FILES})
# add_executable(${KOKKOS_LIB_NAME}_main ${SOURCE_FILES})

# 指定生成的共享库输出路径
set_target_properties(${KOKKOS_LIB_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Kokkos
# TODO: 不管外部使用了什么编译器，与kokkos相关的代码很可能使用的都是nvcc_wrapper，外面的项目可能不需要使用nvcc_wrapper。
find_package(Kokkos CONFIG)  # Kokkos 提供了一个专门为 CMake 配置的文件，其中包含关于库的路径、编译选项等详细信息。
if(Kokkos_FOUND)
  message(STATUS "Found Kokkos: ${Kokkos_DIR} (version \"${Kokkos_VERSION}\")")
endif()

target_link_libraries(${KOKKOS_LIB_NAME} PUBLIC Kokkos::kokkos)


# target_link_libraries(${KOKKOS_LIB_NAME}_main PUBLIC Kokkos::kokkos)

# 如果需要特定的编译选项，可以使用以下行添加：
# target_compile_options(${KOKKOS_LIB_NAME} PRIVATE -Wall -Wextra)

# 如果你的库依赖其他库，你可以在这里链接：
# target_link_libraries(${KOKKOS_LIB_NAME} PUBLIC some_other_library)
