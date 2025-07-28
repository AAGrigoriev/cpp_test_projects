#include "global_context.hpp"

#include <memory>

#include "console_writer.hpp"
#include "file_writer.hpp"

namespace logic {

global_context& global_context::get_instance(std::size_t bulk_size) {
  static global_context context(bulk_size);
  return context;
}

global_context::global_context(std::size_t bulk_size) : bulk_size_(bulk_size) {
  auto c_writer = std::make_unique<console_writer>(console_mutex_);
  auto f_writer =
      std::make_unique<file_writer>("bulk", ".log", open_file_mutex_);

  post_controller_.add_file_writer(std::move(f_writer));
  post_controller_.add_console_writer(std::move(c_writer));
}

std::mutex& global_context::get_console_mutex() {
  return console_mutex_;
}

std::mutex& global_context::get_open_file_mutex() {
  return open_file_mutex_;
}

std::size_t global_context::get_bulk_size() const noexcept {
  return bulk_size_;
}

post_controller& global_context::get_post_controller() {
  return post_controller_;
}

}  // namespace logic
