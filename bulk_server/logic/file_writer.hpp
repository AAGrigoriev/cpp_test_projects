#pragma once

#include <mutex>
#include <string>
#include <string_view>

#include "i_writer.hpp"

namespace logic {

class file_writer : public i_writer {
 public:
  file_writer(std::string_view prefix,
              std::string_view suffix,
              std::mutex& open_file_mutex);

  void write(const command& command) const override;

 private:
  void open_file(const std::string& base_filename, std::ofstream& file) const;
  void open_file_non_blocking(const std::string& base_filename,
                              std::ofstream& file) const;

 private:
  std::string file_prefix_;
  std::string file_suffix_;
  std::mutex& mutex_;
};

}  // namespace logic
