#pragma once

#include <istream>

#include "command_buffer.hpp"
#include "global_context.hpp"

namespace logic {

class controller {
 public:
  controller(global_context& context);

  void process_command(std::istream& stream);

 private:
  void open_brace();
  void close_brace();
  void add_command(std::string&& command);
  void create_command();

 private:
  struct depth {
    int current_depth = {};
    std::size_t bulk_size = {};
  };

 private:
  global_context& context_;
  depth depth_;
  command_buffer command_buffer_;
};
}  // namespace logic
