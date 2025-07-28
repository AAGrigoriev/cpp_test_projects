#include "post_controller.hpp"

namespace logic {

void post_controller::add_console_writer(std::unique_ptr<i_writer> writer) {
  console_writer_ = std::move(writer);
}

void post_controller::add_file_writer(std::unique_ptr<i_writer> writer) {
  file_writer_ = std::move(writer);
}

void post_controller::process_data(const command& command) const {
  file_writer_->write(command);
  console_writer_->write(command);
}

}  // namespace logic
