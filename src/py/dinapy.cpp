#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "lib/dina.h"

namespace py = pybind11;

PYBIND11_MODULE(dinapy, m) {
  py::class_<algo::Algorithms>(m, "Algorithms")
      .def(py::init())
      .def("add", &algo::Algorithms::add)
      .def("sum", &algo::Algorithms::sum)
      .def("group_by_symbol", &algo::Algorithms::group_by_symbol)
      .def("add_async", &algo::Algorithms::add_async)
      .def("factorial", &algo::Algorithms::factorial)
      .def("factorial_no_gil", &algo::Algorithms::factorial,
           py::call_guard<py::gil_scoped_release>())
      .def("async_factorial",
           [](algo::Algorithms* self, std::uint64_t n,
              std::function<void(std::int64_t)> callback) {
             std::int64_t res{0};
             py::gil_scoped_release no_gil{};
             res = self->factorial(n);
             callback(res);
           })
      .def("factorial_parallel", &algo::Algorithms::factorial_parallel);
}
