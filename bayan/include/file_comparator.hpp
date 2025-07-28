#pragma once

#include <algorithm>

#include "file_wrapper.hpp"

namespace bayan {

class IFile_comparator {
 public:
  virtual ~IFile_comparator() = default;
  virtual void add_paths(const group_path&) = 0;
  virtual const parsing_result& duplicates() const = 0;
};

template <typename hash_algo>
class file_comparator : public IFile_comparator {
 public:
  file_comparator(std::size_t block_size) : block_size_(block_size) {}

  void add_paths(const group_path& size_paths) override {
    for (const auto& param : size_paths) {
      v_file_wrapper_.clear();
      auto& path_vector = duplicates_.emplace_back();
      for (const auto& path : param.second) {
        auto temp_wrapper =
            file_wrapper<hash_algo>(path, fs::file_size(path), block_size_);
        if (std::none_of(v_file_wrapper_.begin(), v_file_wrapper_.end(),
                         [&temp_wrapper](const auto& wrapper) {
                           return temp_wrapper == wrapper;
                         })) {
          v_file_wrapper_.push_back(std::move(temp_wrapper));
          path_vector.push_back(path);
        } else {
          path_vector.push_back(path);
        }
      }
    }

    duplicates_.erase(std::remove_if(duplicates_.begin(), duplicates_.end(),
                                     [](const auto& path_vector) {
                                       return path_vector.size() == 1;
                                     }),
                      duplicates_.end());
  }

  [[nodiscard]] const parsing_result& duplicates() const override {
    return duplicates_;
  }

 private:
  std::size_t block_size_;
  std::vector<file_wrapper<hash_algo>> v_file_wrapper_;
  std::vector<std::vector<fs::path>> duplicates_;
};

}  // namespace bayan
