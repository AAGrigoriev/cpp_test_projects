#include "console_writer.hpp"

Reader::ConsoleWriter::ConsoleWriter() : console(std::cout){};

Reader::ConsoleWriter::ConsoleWriter(std::ostream& stream) : console(stream) {}

void Reader::ConsoleWriter::update(const Command& command) {
  auto const& vector = command.getCommand();

  console << "bulk : " << vector.at(0);

  auto iterBeg = vector.begin();
  auto iterEnd = vector.end();

  ++iterBeg;

  while (iterBeg != iterEnd) {
    console << "," << *iterBeg++;
  }

  console << std::endl;
}
