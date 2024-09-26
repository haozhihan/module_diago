#include "diago_dav_subspace.h"
#include "module_base/module_device/types.h"
#include <complex>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(diago_dav_subspace, m) {
  py::class_<Diago_DavSubspace<std::complex<double>, base_device::DEVICE_CPU>>(
      m, "Diago_DavSubspace")
      .def(py::init<const std::vector<double> &, const int &, const int &,
                    const int &, const double &, const int &, const bool &,
                    const diag_comm_info &>())
      .def("get_nbase_x", &Diago_DavSubspace<std::complex<double>,
                                            base_device::DEVICE_CPU>::get_nbase_x)
}