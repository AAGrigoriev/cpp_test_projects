#pragma once

#include <string>

#include "postprocessor_handler.hpp"

namespace async {

class logging_handler : public postprocessor_handler {
 public:
  logging_handler(std::string handler_name);
  void handle_command(s_command&& command) override final;

 private:
  std::string prefix_;
  std::string ending_ = ".log";
};

}  // namespace async
