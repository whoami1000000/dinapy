find_package(GTest CONFIG REQUIRED)

add_executable(test_runner test.cpp)
target_link_libraries(test_runner PRIVATE GTest::gtest algo)

add_test(test_runner test_runner)