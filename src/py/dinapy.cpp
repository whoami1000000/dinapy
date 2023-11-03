#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>

#include "lib/algo.h"

namespace py = pybind11;

PYBIND11_MODULE(dinapy, m) {
  py::class_<algo::Algorithms>(m, "Algorithms")
      .def(py::init())
      .def("add", &algo::Algorithms::add)
      .def("sum", &algo::Algorithms::sum)
      .def("group_by_symbol", &algo::Algorithms::group_by_symbol)
      .def("add_async", &algo::Algorithms::add_async);
}
