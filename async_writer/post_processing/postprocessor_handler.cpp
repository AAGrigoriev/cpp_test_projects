#include "postprocessor_handler.hpp"

namespace async {

void fill_stream(std::ostream& stream, const command::commands& commands) {
  stream << "bulk: ";
  std::string separator = "";
  for (const auto& command : commands) {
    stream << separator << command;
    separator = ", ";
  }
  stream << std::endl;
}

}  // namespace async
