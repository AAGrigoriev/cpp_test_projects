//
// Created by andrei on 22.02.2021.
//

#include "mask.hpp"

#include <boost/algorithm/string/replace.hpp>

namespace bayan {

mask::mask(std::string string_in)
    : reg_(prepare(string_in), std::regex::icase) {}

std::string mask::prepare(std::string prep) {
  boost::replace_all(prep, ".", "\\.");
  boost::replace_all(prep, "*", "\\*");
  boost::replace_all(prep, "?", "\\?");
  boost::replace_all(prep, "\\?", ".");
  boost::replace_all(prep, "\\*", ".*");
  return prep;
}

bool mask::is_valid(const std::string& to_match) {
  return std::regex_search(to_match, reg_);
}

}  // namespace bayan
