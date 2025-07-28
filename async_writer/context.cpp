#include "context.hpp"

#include <memory>

#include "logging_handler.hpp"
#include "output_handler.hpp"
#include "parser.hpp"

namespace async {

context::context()
    : controller_(logging_queue_, output_queue_),
      output_post_controller_(std::make_unique<output_handler>(),
                              output_queue_),
      first_logging_controller_(std::make_unique<logging_handler>("file_1"),
                                logging_queue_),
      second_logging_controller_(std::make_unique<logging_handler>("file_2"),
                                 logging_queue_) {
  output_thread_ =
      std::jthread(&post_controller::run, &output_post_controller_);
  first_logger_thread_ =
      std::jthread(&post_controller::run, &first_logging_controller_);
  second_logger_thread_ =
      std::jthread(&post_controller::run, &second_logging_controller_);
}

void context::process_command(const std::string& command,
                              std::size_t bulk_size) {
  auto result = parser().parse_command(command);
  controller_.set_bulk_size(bulk_size);
  controller_.process_command(std::move(result));
}

context::~context() {
  controller_.stop();
}

}  // namespace async
