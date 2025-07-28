#pragma once

#include <string>
#include <vector>

#include "command.hpp"

namespace logic {

class command_buffer {
 public:
  void store_command(std::string&& command);

  command::time_point get_bulk_start_time() const noexcept;

  command::commands::size_type current_size() const noexcept;

  command create_command();

 private:
  command::commands commands_;
  command::time_point command_start_time_;
};

}  // namespace logic
