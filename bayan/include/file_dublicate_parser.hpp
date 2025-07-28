//
// Created by andrei on 08.03.2021.
//
#pragma once

#include <memory>

#include "file_comparator.hpp"
#include "options.hpp"

namespace bayan {

class file_dublicate_parser {
 public:
  explicit file_dublicate_parser(opt_hash&& hash);

  [[nodiscard]] parsing_result scan_dublicate(const group_path& g_path);

 private:
  std::unique_ptr<IFile_comparator> m_pimpl;
};

}  // namespace bayan
