#include "output_handler.hpp"

#include <iostream>

namespace async {

output_handler::output_handler() {}

void output_handler::handle_command(s_command&& commands) {
  std::lock_guard _(output_mutex);
  fill_stream(std::cout, commands->commands_);
}

}  // namespace async
