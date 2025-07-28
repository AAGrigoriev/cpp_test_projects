#pragma once

#include <mutex>

#include "i_writer.hpp"

namespace logic {

class console_writer : public i_writer {
 public:
  console_writer(std::mutex& console_mutex);
  void write(const command& str) const override;

 private:
  std::mutex& mutex_;
};

}  // namespace logic
