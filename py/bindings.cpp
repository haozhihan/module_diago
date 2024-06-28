// bindings.cpp
#include "example.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(example_module, m)
{
    py::class_<Example>(m, "Example")
        .def(py::init<int>())                 // 绑定构造函数
        .def("getValue", &Example::getValue)  // 绑定 getValue 方法
        .def("setValue", &Example::setValue); // 绑定 setValue 方法
}
