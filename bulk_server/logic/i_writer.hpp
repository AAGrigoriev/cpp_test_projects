#pragma once

#include <ostream>

#include "command.hpp"

namespace logic {

void fill_stream(std::ostream& stream, const command::commands& commands);

class i_writer {
 public:
  virtual void write(const command& str) const = 0;

  virtual ~i_writer() = default;
};

}  // namespace logic
