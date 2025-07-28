#include "dir_parser.hpp"

#include <iostream>

namespace bayan {

dir_parser::dir_parser(opt_dir&& dir)
    : filter_(std::move(dir.filter_opt)), opt_(std::move(dir.scan_opt)) {}

group_path dir_parser::get_group_path() {
  group_path out = scan_dir();
  delete_uniqe_path(out);
  return out;
}

group_path dir_parser::scan_dir() {
  group_path out;
  for (auto& path : opt_.includes_path) {
    if (opt_.recursive) {
      for (fs::recursive_directory_iterator
               it{path, fs::directory_options::skip_permission_denied},
           it_end{};
           it != it_end; ++it) {
        if (filter_.approach_dir((*it).path())) {
          it.disable_recursion_pending();
        } else if (const auto& path = it->path(); filter_.approach_file(path)) {
          out[fs::file_size(path)].push_back(path);
        }
      }
    } else {
      for (fs::directory_iterator
               it{path, fs::directory_options::skip_permission_denied},
           it_end{};
           it != it_end; ++it) {
        std::cout << it->path().string() << std::endl;
        if (const auto& path = it->path(); filter_.approach_file(path)) {
          out[fs::file_size(path)].push_back(path);
        }
      }
    }
  }
  return out;
}

void dir_parser::delete_uniqe_path(group_path& not_uniqe) {
  for (auto it = not_uniqe.begin(); it != not_uniqe.end();) {
    if (it->second.size() < 2)
      it = not_uniqe.erase(it);
    else
      ++it;
  }
}

}  // namespace bayan
