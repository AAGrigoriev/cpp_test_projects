#pragma once

#include <options.hpp>

#include "filter.hpp"

namespace bayan {

class dir_parser {
 public:
  dir_parser(opt_dir&& opt);

  [[nodiscard]] group_path get_group_path();

 private:
  [[nodiscard]] group_path scan_dir();
  void delete_uniqe_path(group_path& not_uniqe);
  template<typename Iter, typename Func>
  void none_recursive_traversal(const fs::path& path, Func func);

  filter_dir filter_;
  opt_scan opt_;
};

template<typename Iter, typename Func>
void none_recursive_traversal(const fs::path& path, Func func) {

}

}  // namespace bayan
