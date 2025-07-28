#include <chrono>

#include "cout_writer.hpp"
#include "file_writer.hpp"
#include "reader.hpp"


int main() {
  async::reader reader;
  auto cout_writer = async::cout_writer::create("cout_writer", 0, reader);
  cout_writer->create_process();
  cout_writer->create_process();
  cout_writer->create_process();
  cout_writer->create_process();
  cout_writer->create_process();
  cout_writer->create_process();

  auto file_writer = async::file_writer::create("file_writer", 0, reader); 
  file_writer->create_process();
  file_writer->create_process();
  file_writer->create_process();
  file_writer->create_process();
  file_writer->create_process();
  file_writer->create_process();

  for (auto i = 0; i < 10000; ++i) {
    reader.run("bla bla bla { bla bla }");
  }
  
  return 0;
}
