#pragma once

#include <filesystem>
#include <vector>

#include "mask.hpp"
#include "options.hpp"

namespace bayan {

class filter_dir {
 public:
  explicit filter_dir(opt_filter &&filter);

  bool approach_dir(const fs::path &path);
  bool approach_file(const fs::path &path);

 private:
  opt_filter filter_opt_;
  std::vector<mask> filter_mask_;
};

}  // namespace bayan