#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace logic {

struct command {
  using commands = std::vector<std::string>;
  using time_point = std::chrono::time_point<std::chrono::steady_clock>;

  command(command&& command) = default;
  command(const command& command) = default;
  command(commands&& commands, time_point time_point);

  commands commands_;
  time_point time_point_;
};

}  // namespace logic
