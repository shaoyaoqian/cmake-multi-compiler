cmake_minimum_required(VERSION 3.27)
option(ENABLE_FEATURE "Enable feature" ON)

set(CMAKE_CXX_COMPILER /home/kokkos/spack/opt/spack/linux-ubuntu20.04-icelake/gcc-11.4.0/gcc-13.2.0-4hec755h2hicwphybea4n37xb5hue7gg/bin/g++)
set(CMAKE_C_COMPILER /home/kokkos/spack/opt/spack/linux-ubuntu20.04-icelake/gcc-11.4.0/gcc-13.2.0-4hec755h2hicwphybea4n37xb5hue7gg/bin/gcc)

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

add_library(${KOKKOS_LIB_NAME} STATIC IMPORTED GLOBAL)
set_target_properties(${KOKKOS_LIB_NAME} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/your_library/include"
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/your_library/build/libyour_library.a"
)

# 确保 ${KOKKOS_LIB_NAME}_build 先于 ${KOKKOS_LIB_NAME} 被构建
add_dependencies(${KOKKOS_LIB_NAME} ${KOKKOS_LIB_NAME}_build)


project(ProjectName)
add_executable(haha main.cpp)

target_link_libraries(haha PRIVATE your_library)


