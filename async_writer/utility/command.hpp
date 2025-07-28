#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace async {

struct command {
  using commands = std::vector<std::string>;
  using time_point = std::chrono::time_point<std::chrono::steady_clock>;

  command(command&& command) noexcept;
  command(commands&& commands, time_point time_point);

  bool operator==(const command& other);

  std::vector<std::string> commands_;
  time_point time_point_;
};

}  // namespace async
