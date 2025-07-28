#pragma once

#include <thread>

#include "post_processing/postprocessor.hpp"
#include "processing/controller.hpp"

namespace async {

class context {
 public:
  context();
  ~context();

  void process_command(const std::string& command, std::size_t bulk_count);

 private:
  s_command_queue logging_queue_ = std::make_shared<n_queue>();
  s_command_queue output_queue_ = std::make_shared<n_queue>();
  controller controller_;

  post_controller output_post_controller_;
  post_controller first_logging_controller_;
  post_controller second_logging_controller_;

  std::jthread first_logger_thread_;
  std::jthread second_logger_thread_;
  std::jthread output_thread_;
};

}  // namespace async
