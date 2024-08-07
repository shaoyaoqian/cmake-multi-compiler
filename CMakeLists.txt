cmake_minimum_required(VERSION 3.27)
option(ENABLE_FEATURE "Enable feature" ON)

# set(CMAKE_CXX_COMPILER nvcc)
# set(CMAKE_C_COMPILER nvcc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


project(ProjectName LANGUAGES CXX CUDA)
add_executable(haha main.cpp)

set(KOKKOS_LIB_NAME your_library)
if(ENABLE_FEATURE)
   # 定义自定义命令以生成共享库
    add_custom_command(
        OUTPUT "${CMAKE_BINARY_DIR}/lib/libyour_library.so"
        COMMAND cmake -B build -S . 
        COMMAND cmake --build build
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/your_library"
        COMMENT "Generating shared library ${KOKKOS_LIB_NAME}"
    )
    # 添加依赖关系：确保自定义命令在创建目标之前执行
    add_custom_target(${KOKKOS_LIB_NAME}_build ALL
        DEPENDS "${CMAKE_BINARY_DIR}/lib/libyour_library.so"
    )
endif()

# add_library(tbb SHARED IMPORTED GLOBAL)
add_library(${KOKKOS_LIB_NAME} SHARED IMPORTED GLOBAL)
set_target_properties(${KOKKOS_LIB_NAME} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/your_library/include"
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/your_library/build/lib/libyour_library.so"
)

# 确保 ${KOKKOS_LIB_NAME}_build 先于 ${KOKKOS_LIB_NAME} 被构建
add_dependencies(${KOKKOS_LIB_NAME} ${KOKKOS_LIB_NAME}_build)

target_link_libraries(haha PUBLIC your_library)

find_package(Eigen3 REQUIRED)
target_link_libraries(haha PUBLIC Eigen3::Eigen)
