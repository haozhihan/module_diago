cmake_minimum_required(VERSION 3.15...3.27)
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

# 添加子目录
add_subdirectory(src)

set(SOURCES
    src/binding.cpp
)

# 查找 OpenBLAS 库
find_package(BLAS REQUIRED)

# 查找 LAPACK 库
find_package(LAPACK REQUIRED)

pybind11_add_module(_py_dav MODULE ${SOURCES})
target_include_directories(_py_dav PRIVATE src)
target_link_libraries(
    _py_dav 
    PRIVATE 
    pybind11::headers 
    diago 
    device
    ${OpenBLAS_LIBRARIES}
    ${LAPACK_LIBRARIES}
)

target_compile_definitions(_py_dav PRIVATE VERSION_INFO=${PROJECT_VERSION})

set(TARGET_PACK module_diago)
set(CMAKE_INSTALL_RPATH "${PYTHON_SITE_PACKAGES}/${TARGET_PACK}")
set_target_properties(_py_dav PROPERTIES INSTALL_RPATH "$ORIGIN")
set_target_properties(device PROPERTIES INSTALL_RPATH "$ORIGIN")
set_target_properties(diago PROPERTIES INSTALL_RPATH "$ORIGIN")

install(TARGETS _py_dav device DESTINATION ${TARGET_PACK})
install(TARGETS _py_dav diago DESTINATION ${TARGET_PACK})