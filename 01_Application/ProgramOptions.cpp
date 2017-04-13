
#include <boost/program_options.hpp>
#include <boost/program_options/errors.hpp>
#include <iostream>

namespace opt = boost::program_options;

int main(int argc, char **argv) {
  opt::options_description desc("All options");

  desc.add_options()
    // 'a' and 'o' are short options, require() could be used to mark required options
    ("apples,a", opt::value<int>()->default_value(10), "how many apples do you have")
    ("oranges,o", opt::value<int>(), "how many oranges do you have")
    ("name", opt::value<std::string>(), "your name")
    ("help", "produce help message")
  ;

  opt::variables_map vm;

  opt::store(opt::parse_command_line(argc, argv, desc), vm);
  opt::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  try {
    opt::store(
      opt::parse_config_file<char>("apples_oranges.cfg", desc),
      vm
    );
  } catch (const opt::reading_file& e) {
    std::cout << "Failed to open file 'apples_oranges.cfg': "
      << e.what();
  }

  opt::notify(vm);
  if (vm.count("name")) {
    std::cout << "Hi, " << vm["name"].as<std::string>() << "!\n";
  }

  std::cout << "Fruits count: "
    << vm["apples"].as<int>() + vm["oranges"].as<int>()
    << "\n";

  return 0;
}
