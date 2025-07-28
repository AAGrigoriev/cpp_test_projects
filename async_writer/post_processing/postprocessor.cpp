#include "postprocessor.hpp"

namespace async {

post_controller::post_controller(postprocessor_handler::u_handler&& handler,
                                 s_command_queue command_queue)
    : handler_(std::move(handler)), command_queue_(command_queue) {}

void post_controller::run() {
  s_command result_command;
  while (command_queue_->try_pop(result_command)) {
    handler_->handle_command(std::move(result_command));
  }
}

}  // namespace async
