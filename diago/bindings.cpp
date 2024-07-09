#include "diago_dav_subspace.h"
#include "module_base/module_device/types.h"
#include <complex>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// #include <pybind11/complex.h>
#include "diagh.h"

namespace py = pybind11;

PYBIND11_MODULE(diago_dav_subspace, m) {
  py::class_<hsolver::diag_comm_info>(m, "diag_comm_info")
      .def(py::init<const int &, const int &>())
      .def_readonly("rank", &hsolver::diag_comm_info::rank)
      .def_readonly("nproc", &hsolver::diag_comm_info::nproc);
  
  py::class_<hsolver::Diago_DavSubspace<std::complex<double>, base_device::DEVICE_CPU>>(
      m, "Diago_DavSubspace")
      .def(py::init<const std::vector<double> &, const int &, const int &,
                    const int &, const double &, const int &, const bool &,
                    const hsolver::diag_comm_info &>())
      .def("get_nbase_x", &hsolver::Diago_DavSubspace<std::complex<double>,
                                            base_device::DEVICE_CPU>::get_nbase_x);
}