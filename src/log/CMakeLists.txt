find_package(spdlog CONFIG REQUIRED)
add_library(logging logging.h)
target_link_libraries(logging PUBLIC spdlog::spdlog)