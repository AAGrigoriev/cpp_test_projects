#include "com_parser.hpp"
#include "dir_parser.hpp"
#include "file_dublicate_parser.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
  bayan::command_parser parser{argc, argv};

  auto opt_parser = parser.parse_data();

  if (!opt_parser) {
    return 0;
  }

  bayan::dir_parser dir_parser(std::move(opt_parser.value().dir_opt));
  auto result = dir_parser.get_group_path();
  bayan::file_dublicate_parser file_parser(
      std::move(opt_parser.value().hash_opt));

  const auto res = file_parser.scan_dublicate(result);

  for (const auto& files : res) {
    for (const auto& path : files) {
      std::cout << path << std::endl;
    }
    std::cout << std::endl;
  }

  return 0;
}
