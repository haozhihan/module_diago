# 添加包含目录
include_directories(${CMAKE_SOURCE_DIR}/diago)

# 设置源文件列表
set(DIAGO_SOURCES
    diagh_consts.cpp
    diago_dav_subspace.cpp

    module_base/parallel_reduce.cpp
    
    module_base/module_device/device.cpp
    module_base/module_device/memory_op.cpp
    
    module_hsolver/kernels/dngvd_op.cpp
    module_hsolver/kernels/math_kernel_op.cpp
)

# 添加库
add_library(diago ${DIAGO_SOURCES})

# 添加子目录
add_subdirectory(module_base)
add_subdirectory(module_hsolver)