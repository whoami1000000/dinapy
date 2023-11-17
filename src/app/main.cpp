#include <iostream>

#include <spdlog/spdlog.h>
#include <cxxopts.hpp>

#include "lib/dina.h"
#include "log/logging.h"
#include "version.h"

int main(int argc, char** argv) {
  cxxopts::Options options{
      PROJECT_NAME,
      "Simple app to demonstrate CICD, debian package building and versioning"};

  options
      .positional_help("Simple app to demonstrate CICD, debian package building and versioning")  //
      .show_positional_help();                                                                    //

  options.add_options()                //
      ("help,h", "Prints help")        //
      ("version,v", "Prints version")  //
      ("log", "Log file path prefix", cxxopts::value<std::string>());

  cxxopts::ParseResult pr = options.parse(argc, argv);

  if (pr.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  } else if (pr.count("version")) {
    std::cout << PROJECT_VER << std::endl;
    return 0;
  }

  std::string prefix{};
  if (pr.count("log")) {
    prefix = pr["log"].as<std::string>();
  }
  configure_logger(true, prefix);
  spdlog::info("{} has been started", PROJECT_NAME);

  algo::Algorithms a{};
  spdlog::debug("{} + {} = {}", 2, 2, a.add(2, 2));

  std::vector<int> numbers{1, 2, 3, 4};
  int sum = a.sum(numbers);
  spdlog::debug("sum of numbers = {}", sum);

  //  a.factorial_async(5, [](auto res) { spdlog::debug("factorial_async({})={}", 5, res); });
  //  a.factorial_async(6, [](auto res) { spdlog::debug("factorial_async({})={}", 6, res); });
  //  a.factorial_async(7, [](auto res) { spdlog::debug("factorial_async({})={}", 7, res); });
  //
  //  std::this_thread::sleep_for(std::chrono::seconds{10});

  return 0;
}
