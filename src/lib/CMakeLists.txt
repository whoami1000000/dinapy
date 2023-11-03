enable_language(Fortran)

add_library(dina_fortran STATIC dina.f90)

add_library(dina SHARED dina.cpp)
target_link_libraries(dina dina_fortran gfortran)

add_library(dina_static STATIC dina.cpp)
target_link_libraries(dina_static dina_fortran gfortran)
set_property(TARGET dina_static PROPERTY POSITION_INDEPENDENT_CODE ON)