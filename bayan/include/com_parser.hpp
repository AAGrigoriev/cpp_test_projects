#pragma once

#include <boost/program_options.hpp>
#include <optional>

#include "options.hpp"

namespace bayan {

class command_parser {
 public:
  command_parser(int argc, char* argv[]);

  [[nodiscard]] std::optional<opt_data> parse_data();

 private:
  bpo::variables_map mp_;
  bpo::options_description desc_;
};

}  // namespace bayan
