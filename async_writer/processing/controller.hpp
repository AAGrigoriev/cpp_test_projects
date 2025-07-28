#pragma once

#include "accumulator.hpp"
#include "utility.hpp"

namespace async {

class controller {
 public:
  controller(s_command_queue logging_queue, s_command_queue output_queue);

  void set_bulk_size(std::size_t max_depth) noexcept;

  void process_command(std::vector<std::string>&& command);

  void stop();

 private:
  struct depth {
    std::size_t bulk_size{};
    int current_depth{};
  };

 private:
  s_command_queue logging_queue_;
     s_command_queue output_queue_;
  accumulator command_accumulator_;
  depth depth_;
};

}  // namespace async
