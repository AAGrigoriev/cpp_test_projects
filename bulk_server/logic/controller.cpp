#include "controller.hpp"

#include <cassert>
#include <string>

#include "global_context.hpp"
#include "thread_pool.hpp"

namespace logic {

controller::controller(global_context& context)
    : context_(context), depth_{0, context_.get_bulk_size()} {}

void controller::process_command(std::istream& stream) {
  std::string line;

  while (std::getline(stream, line)) {
    if (line == "{") {
      open_brace();
    } else if (line == "}") {
      close_brace();
    } else {
      add_command(std::move(line));
    }
  }

  if (command_buffer_.current_size()) {
    create_command();
  }
}

void controller::open_brace() {
  if (depth_.current_depth == 0 && command_buffer_.current_size()) {
    create_command();
    ++depth_.current_depth;
  } else {
    ++depth_.current_depth;
  }
}

void controller::close_brace() {
  if (depth_.current_depth == 0) {
    throw std::logic_error("incorrect sequence of characters { and }");
  }

  --depth_.current_depth;

  if (depth_.current_depth == 0 && command_buffer_.current_size()) {
    create_command();
  }
}

void controller::add_command(std::string&& command) {
  command_buffer_.store_command(std::move(command));
  if (depth_.current_depth == 0 &&
      command_buffer_.current_size() == depth_.bulk_size) {
    create_command();
  }
}

void controller::create_command() {
  assert(command_buffer_.current_size());

  auto commands = command_buffer_.create_command();

  auto job = [com = std::move(commands)]() {
    global_context::get_instance().get_post_controller().process_data(com);
  };

  utility::thread_pool::get_instance().enqueue(std::move(job));
}

}  // namespace logic
