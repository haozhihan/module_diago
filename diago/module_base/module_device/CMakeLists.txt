# 添加包含目录
include_directories(${CMAKE_SOURCE_DIR}/diago/module_base/module_device)

# 设置源文件列表
set(DEVICE_SOURCES
    device.cpp
    memory_op.cpp
)

# 添加库
add_library(device ${DEVICE_SOURCES})

# 链接库
target_link_libraries(device)
