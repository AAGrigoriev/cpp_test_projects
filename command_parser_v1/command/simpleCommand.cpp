#include <simpleCommand.hpp>

namespace Reader {
void Command::put_command(std::string&& command) {
  if (stringCommand.empty()) {
    time_point = std::chrono::system_clock::now();
  }

  stringCommand.emplace_back(std::move(command));
}

std::string Command::getTime() const {
  auto time = std::chrono::duration_cast<std::chrono::seconds>(
                  time_point.time_since_epoch())
                  .count();

  return std::to_string(time);
}

void Command::clearCommand() {
  stringCommand.clear();
}

std::vector<std::string> const& Command::getCommand() const {
  return stringCommand;
}
}  // namespace fileReader
