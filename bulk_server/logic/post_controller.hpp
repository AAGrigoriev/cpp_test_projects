#pragma once

#include <memory>

#include "command.hpp"
#include "i_writer.hpp"

namespace logic {

class post_controller {
 public:
  void add_file_writer(std::unique_ptr<i_writer> writer);
  void add_console_writer(std::unique_ptr<i_writer> writer);

  void process_data(const command& command) const;

 private:
  std::unique_ptr<i_writer> file_writer_;
  std::unique_ptr<i_writer> console_writer_;
};

}  // namespace logic
