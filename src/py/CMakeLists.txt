find_package(pybind11 REQUIRED)
pybind11_add_module(dinapy dinapy.cpp)
target_link_libraries(dinapy PRIVATE dina_static)