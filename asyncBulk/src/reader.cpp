#include "reader.hpp"

#include <regex>
#include <string>
#include <string_view>
#include <vector>


namespace async {

namespace {

std::vector<std::string> split_string(const std::string& string, std::string_view regex) {
  std::regex reg(regex.data());
  std::sregex_token_iterator first{string.begin(), string.end(), reg, -1};
  return {first, {}};
}

} // namespace

reader::reader(const std::size_t command_size)
    : state_f_(&reader::plain), command_size_(command_size), nested_level_{0} 
  {}


void reader::run(const std::string& data) {
  state_f_ = &reader::plain;
  for (auto&& string : split_string(data, " ")) {
    state_f_(this, std::move(string));
  }
}


void reader::plain(std::string&& token) {
  if (token == "{") {
    if (!command_.empty()) {
      flush_command();
    }
    state_f_ = &reader::block;
  } else if (token != "{") {
    command_.push_command(std::move(token));
    if (command_.get_command().size() == command_size_) {
      flush_command();
    }
  }
}


void reader::block(std::string&& token) {
  if (token == "{") {
    state_f_ = &reader::nested;
  } else if (token == "}") {
    if (!command_.empty()) {
      flush_command();
    }
  } else {
    command_.push_command(std::move(token));
  }
}


void reader::nested(std::string&& token) {
  if (token == "{") {
    ++nested_level_;
  } else if (token == "}") {
    nested_level_ = nested_level_ == 0 ? 0 : --nested_level_; ///< Дополнительная проверка. Пропускаем лишние "}".
    if (nested_level_ == 0) {
      state_f_ = &reader::block;
    }
  } else {
    command_.push_command(std::move(token));
  }
}


void reader::flush_command() {
  notify(command_);
  command_.clear_command();
}
} // namespace async
