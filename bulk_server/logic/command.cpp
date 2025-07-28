#include "command.hpp"

namespace logic {

command::command(commands&& commands, time_point time_point)
    : commands_(std::move(commands)), time_point_(time_point) {}

}  // namespace logic
