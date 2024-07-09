cmake_minimum_required(VERSION 3.10)
project(diago_dav_subspace)

# 查找 OpenBLAS 库
find_package(BLAS REQUIRED)

# 查找 LAPACK 库
find_package(LAPACK REQUIRED)

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

# 添加子目录
add_subdirectory(module_base)
add_subdirectory(module_hsolver)

# 添加库
add_library(diago SHARED ${DIAGO_SOURCES})
target_link_libraries(diago PRIVATE ${OpenBLAS_LIBRARIES} ${LAPACK_LIBRARIES})


add_subdirectory(pybind11)
pybind11_add_module(diago_dav_subspace bindings.cpp)

target_link_libraries(diago_dav_subspace PRIVATE diago )