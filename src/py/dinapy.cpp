#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "lib/dina.h"
#include "log/logging.h"

namespace py = pybind11;

PYBIND11_MODULE(dinapy, m) {
  py::enum_<spdlog::level::level_enum>(m, "LoggerLevel")
      .value("TRACE", spdlog::level::level_enum::trace)
      .value("DEBUG", spdlog::level::level_enum::debug)
      .value("INFO", spdlog::level::level_enum::info)
      .value("WARN", spdlog::level::level_enum::warn)
      .value("ERR", spdlog::level::level_enum::err)
      .value("CRITICAL", spdlog::level::level_enum::critical)
      .value("OFF", spdlog::level::level_enum::off)
      .export_values();

  m.def("configure_logger",                                    //
        &configure_logger,                                     //
        "A function which configures a logger",                //
        py::arg("console") = true,                             //
        py::arg("log_file_prefix") = std::string_view{},       //
        py::arg("level") = spdlog::level::level_enum::debug);  //

  py::class_<algo::Algorithms>(m, "Algorithms")
      .def(py::init())
      .def("add", &algo::Algorithms::add)
      .def("sum", &algo::Algorithms::sum)
      .def("group_by_symbol", &algo::Algorithms::group_by_symbol)
      .def("add_async", &algo::Algorithms::add_async)
      .def("factorial", &algo::Algorithms::factorial)
      .def("factorial_no_gil",
           &algo::Algorithms::factorial,
           py::call_guard<py::gil_scoped_release>())
      .def("async_factorial",
           [](algo::Algorithms* self, std::int64_t n, std::function<void(std::int64_t)> callback) {
             std::int64_t res{0};
             py::gil_scoped_release no_gil{};
             res = self->factorial(n);
             callback(res);
           })
      .def("factorial_parallel", &algo::Algorithms::factorial_parallel)
      .def("factorial_async", &algo::Algorithms::factorial_async);
}
