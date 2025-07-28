#include "command_buffer.hpp"

namespace logic {

void command_buffer::store_command(std::string&& command) {
  if (commands_.empty()) {
    command_start_time_ = std::chrono::steady_clock::now();
  }

  commands_.push_back(std::move(command));
}

command::time_point command_buffer::get_bulk_start_time() const noexcept {
  return command_start_time_;
}

command::commands::size_type command_buffer::current_size() const noexcept {
  return commands_.size();
}

command command_buffer::create_command() {
  command result(std::move(commands_), command_start_time_);
  commands_.clear();
  return result;
}

}  // namespace logic
