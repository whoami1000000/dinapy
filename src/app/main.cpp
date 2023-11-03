#include <iostream>

#include <boost/program_options.hpp>

#include "lib/algo.h"
#include "version.h"

int main(int argc, char** argv) {
  namespace po = boost::program_options;
  po::options_description options{"versioning_app"};
  options.add_options()                                            //
      ("help,h", "Simple app to demonstrate CICD and versioning")  //
      ("version,v", "Prints version");                             //
  po::variables_map vm{};
  po::store(po::parse_command_line(argc, argv, options), vm);
  po::notify(vm);

  if (vm.contains("help")) {
    std::cout << options << std::endl;
    return 0;
  } else if (vm.contains("version")) {
    std::cout << PROJECT_VER << std::endl;
    return 0;
  }

  algo::Algorithms a{};
  std::cout << "2 + 2 = " << a.add(2, 2) << std::endl;
  return 0;
}
