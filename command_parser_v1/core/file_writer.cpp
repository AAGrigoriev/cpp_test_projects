#include "file_writer.hpp"

#include <fstream>

void Reader::FileWriter::update(const Command& command) {
  std::ofstream file_writer("bulk" + command.getTime() + ".log");

  if (!file_writer.is_open())
    return;

  auto& vector_command = command.getCommand();

  file_writer << "bulk : " << vector_command.at(0);

  auto iterBeg = vector_command.begin();
  auto iterEnd = vector_command.end();
  ++iterBeg;

  while (iterBeg != iterEnd) {
    file_writer << " ," << *iterBeg++;
  }
  file_writer << std::endl;

  file_writer.close();
}
