#include "console_writer.hpp"
#include "file_writer.hpp"
#include "reader.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "N :\n  " << argv[0];
    return EXIT_FAILURE;
  }

  std::cout << argv[1] << std::endl;

  Reader::Reader lineReader(std::stoul(argv[1]));
  auto file_writer = std::make_shared<Reader::FileWriter>();
  auto console_writer = std::make_shared<Reader::ConsoleWriter>();

  lineReader.attach(file_writer);
  lineReader.attach(console_writer);
  lineReader.run();
  return 0;
}
