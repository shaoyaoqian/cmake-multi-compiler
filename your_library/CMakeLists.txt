set(LIB_NAME your_library)

if(ENABLE_FEATURE)
   # 定义自定义命令以生成共享库
    add_custom_command(
        OUTPUT "${CMAKE_BINARY_DIR}/lib/libyour_library.so"
        COMMAND g++ -fPIC -c "${CMAKE_SOURCE_DIR}/your_library/example.cpp" -o "${CMAKE_SOURCE_DIR}/your_library/example.o"
        COMMAND g++ -shared -o "${CMAKE_SOURCE_DIR}/your_library/libyour_library.so" "${CMAKE_SOURCE_DIR}/your_library/example.o"
        COMMAND rm "${CMAKE_SOURCE_DIR}/your_library/example.o"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/your_library"
        COMMENT "Generating shared library ${LIB_NAME}"
    )
    # 添加依赖关系：确保自定义命令在创建目标之前执行
    add_custom_target(${LIB_NAME}_build ALL
        DEPENDS "${CMAKE_BINARY_DIR}/lib/libyour_library.so"
    )
endif()

add_library(${LIB_NAME} SHARED IMPORTED GLOBAL)
set_target_properties(${LIB_NAME} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/your_library/include"
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/your_library/libyour_library.so"
)

# 确保 ${LIB_NAME}_build 先于 ${LIB_NAME} 被构建
# add_dependencies(${LIB_NAME} ${LIB_NAME}_build)

