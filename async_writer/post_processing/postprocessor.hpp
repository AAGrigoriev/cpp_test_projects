#pragma once

#include "postprocessor_handler.hpp"
#include "utility.hpp"

namespace async {

class post_controller {
 public:
  post_controller(postprocessor_handler::u_handler&& handler,
                  s_command_queue command_queue);

  void run();

 private:
  postprocessor_handler::u_handler handler_;
  s_command_queue command_queue_;
};

}  // namespace async
