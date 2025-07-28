#pragma once

#include <memory>
#include <ostream>

#include "utility.hpp"

namespace async {

void fill_stream(std::ostream& stream, const command::commands& commands);

class postprocessor_handler {
 public:
  using u_handler = std::unique_ptr<postprocessor_handler>;

  virtual ~postprocessor_handler() = default;

 public:
  virtual void handle_command(s_command&& command) = 0;
};

}  // namespace async
