#include "logging_handler.hpp"

#include <fstream>
#include <string>

namespace async {

logging_handler::logging_handler(std::string handler_name)
    : prefix_(handler_name + "_bulk") {}

void logging_handler::handle_command(s_command&& commands) {
  const auto file_name =
      prefix_ +
      std::to_string(commands->time_point_.time_since_epoch().count()) +
      ending_;

  std::ofstream file_stream(file_name);
  if (!file_stream.is_open()) {
    return;  // todo: check
  }
  fill_stream(file_stream, commands->commands_);
}

}  // namespace async
