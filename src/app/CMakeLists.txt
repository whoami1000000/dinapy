find_package(cxxopts CONFIG REQUIRED)

add_executable(dina_app main.cpp)
target_include_directories(dina_app PRIVATE ${CMAKE_BINARY_DIR} ${Boost_INCLUDE_DIR})
target_link_libraries(dina_app dina cxxopts::cxxopts)