#include "console_writer.hpp"

#include <iostream>
#include <mutex>

namespace logic {

console_writer::console_writer(std::mutex& mutex) : mutex_(mutex) {}

void console_writer::write(const command& command) const {
  std::lock_guard _(mutex_);

  fill_stream(std::cout, command.commands_);
}

}  // namespace logic
