#include <iostream>

#include <cxxopts.hpp>

#include "lib/dina.h"
#include "version.h"

int main(int argc, char** argv) {
  cxxopts::Options options{
      PROJECT_NAME,
      "Simple app to demonstrate CICD, debian package building and versioning"};

  options
      .positional_help(
          "Simple app to demonstrate CICD, debian package building and "
          "versioning")
      .show_positional_help();
  options.add_options()                 //
      ("help,h", "Prints help")         //
      ("version,v", "Prints version");  //

  cxxopts::ParseResult pr = options.parse(argc, argv);

  if (pr.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  } else if (pr.count("version")) {
    std::cout << PROJECT_VER << std::endl;
    return 0;
  }

  algo::Algorithms a{};
  std::cout << "2 + 2 = " << a.add(2, 2) << std::endl;
  return 0;
}
