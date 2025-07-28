#include "file_writer.hpp"

#include <filesystem>
#include <fstream>

namespace logic {

file_writer::file_writer(std::string_view prefix,
                         std::string_view suffix,
                         std::mutex& open_file_mutex)
    : file_prefix_(prefix), file_suffix_(suffix), mutex_(open_file_mutex) {}

void file_writer::open_file_non_blocking(const std::string& base_filename,
                                         std::ofstream& file) const {
  std::size_t i = 0;
  std::filesystem::path path(base_filename);
  while (std::filesystem::exists(path)) {
    ++i;
    path = base_filename + std::to_string(i);
  }
  file.open(path);
}

void file_writer::open_file(const std::string& base_filename,
                            std::ofstream& file) const {
  std::lock_guard _(mutex_);
  open_file_non_blocking(base_filename, file);
}

void file_writer::write(const command& command) const {
  const auto file_name =
      file_prefix_ +
      std::to_string(command.time_point_.time_since_epoch().count()) +
      file_suffix_;

  std::ofstream file_stream;
  open_file(file_name, file_stream);
  fill_stream(file_stream, command.commands_);
  file_stream.close();
}

}  // namespace logic
