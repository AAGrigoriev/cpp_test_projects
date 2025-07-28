#include "command.hpp"


namespace async {

void command::push_command(std::string &&command) {
  if (command_.empty()) {
    time_ = std::to_string(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count());
  }
  command_.push_back(std::move(command));
}


void command::clear_command() {
  command_.clear();
}


const std::string &command::get_time() const { return time_; }


const std::vector<std::string> &command::get_command() const { return command_; }


bool command::empty() const { return command_.empty(); }


std::ostream& operator<<(std::ostream& a_osOut, const command& command) {
  for (auto command_it = command.command_.begin();
       command_it != command.command_.cend(); ++command_it) {
    if (command_it != command.command_.begin()) {
      a_osOut << ", ";
    }
    a_osOut << *command_it;
  }
  return a_osOut;
}
} // namespace async
