//
// Created by andrei on 08.03.2021.
//

#include "file_dublicate_parser.hpp"

namespace bayan {

file_dublicate_parser::file_dublicate_parser(opt_hash&& option) {
  switch (option.h_algo) {
    case hash_algo::crc_32:
      m_pimpl =
          std::make_unique<file_comparator<std::size_t>>(option.block_size);
      break;
    case hash_algo::md5:
      m_pimpl =
          std::make_unique<file_comparator<md5digest_t>>(option.block_size);
      break;
    default:
      break;
  }
}

parsing_result file_dublicate_parser::scan_dublicate(const group_path& g_path) {
  m_pimpl->add_paths(g_path);
  return m_pimpl->duplicates();
}
}  // namespace bayan
