//
// Created by andrei on 22.02.2021.
#include "filter.hpp"

#include <regex>

namespace bayan {

filter_dir::filter_dir(opt_filter&& opt_filter)
    : filter_opt_(std::move(opt_filter)) {
  for (auto& mask : filter_opt_.mask_to_file) {
    filter_mask_.emplace_back(mask);
  }
}

bool filter_dir::approach_dir(const fs::path& path) {
  return std::any_of(
      filter_opt_.exclude_path.begin(), filter_opt_.exclude_path.end(),
      [&path](fs::path& filter_path) { return path == filter_path; });
}

bool filter_dir::approach_file(const fs::path& path) {
  if (fs::is_regular_file(path) &&
      fs::file_size(path) >= filter_opt_.min_file_size) {
    return std::any_of(
        filter_mask_.begin(), filter_mask_.end(),
        [&path](mask& mask_) { return mask_.is_valid(path.string()); });
  }
  return false;
}
}  // namespace bayan
