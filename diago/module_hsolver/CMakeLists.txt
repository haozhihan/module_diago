# 添加包含目录
include_directories(${CMAKE_SOURCE_DIR}/diago/module_hsolver/kernels)

# 设置源文件列表
set(KERNELS_SOURCES
    dngvd_op.cpp
    math_kernel_op.cpp
)

# 添加库
add_library(kernels ${KERNELS_SOURCES})

# 链接库
target_link_libraries(kernels)
