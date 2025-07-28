#include "parser.hpp"

#include <boost/spirit/home/x3.hpp>

namespace async {

// text\ntext\n{\n\n}\n

namespace x3 = boost::spirit::x3;

struct bracket_tag;

auto first_rule = x3::rule<bracket_tag, std::string>() =
    x3::string("{") | x3::string("}") | +(x3::char_ - x3::eol);

auto end_rule = first_rule % x3::eol;

std::vector<std::string> parser::parse_command(std::string_view input_data) {
  std::vector<std::string> result;
  if (auto ok =
          x3::parse(input_data.begin(), input_data.end(), end_rule, result);
      ok) {
    return result;
  }

  // Запись ошибки.

  return {};
}

}  // namespace async
