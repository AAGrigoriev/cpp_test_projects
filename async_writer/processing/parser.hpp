#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace async {

class parser {
 public:
  std::vector<std::string> parse_command(std::string_view input_text);
};

}  // namespace async
