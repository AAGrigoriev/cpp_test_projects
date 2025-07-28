#include "command.hpp"

namespace async {

command::command(command&& command) noexcept
    : commands_(std::move(command.commands_)),
      time_point_(command.time_point_) {}

command::command(commands&& commands, time_point time_point)
    : commands_(std::move(commands)), time_point_(time_point) {}

bool command::operator==(const command& command) {
  return commands_ == command.commands_ && time_point_ == command.time_point_;
}

}  // namespace async
