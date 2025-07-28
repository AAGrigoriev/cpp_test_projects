#pragma once

#include <cstddef>
#include <mutex>

#include "post_controller.hpp"

namespace logic {

class global_context {
 public:
  global_context(const global_context&) = delete;
  global_context& operator=(const global_context&) = delete;
  global_context(global_context&&) = delete;
  global_context& operator=(global_context&&) = delete;

 public:
  static global_context& get_instance(std::size_t bulk_size = 1);

  std::mutex& get_console_mutex();

  std::mutex& get_open_file_mutex();

  std::size_t get_bulk_size() const noexcept;

  post_controller& get_post_controller();

 private:
  global_context(std::size_t bulk_size);

 private:
  std::size_t bulk_size_;
  post_controller post_controller_;
  std::mutex console_mutex_;
  std::mutex open_file_mutex_;
};

}  // namespace logic
