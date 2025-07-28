#pragma once

#include <assert.h>
#include <algorithm>
#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <fstream>
#include <vector>

#include "options.hpp"

namespace bayan {

template <typename T>
inline T calc_check_sum(const char* buf, std::size_t size);

template <>
inline std::size_t calc_check_sum(const char* buf, std::size_t size) {
  boost::crc_32_type result;
  result.process_bytes(buf, size);
  return result.checksum();
}

using md5digest_t = std::array<unsigned int, 4>;

template <>
inline md5digest_t calc_check_sum(const char* buf, std::size_t size) {
  boost::uuids::detail::md5 hash;
  boost::uuids::detail::md5::md5::digest_type digest;
  hash.process_bytes(buf, size);
  hash.get_digest(digest);
  return {digest[0], digest[1], digest[2], digest[3]};
}

/*
  @brief Класс, хранящий хеши файла и позволяющий сравнивать файлы между собой
*/
template <typename T>
class file_wrapper {
 public:
  using type_it = typename std::vector<T>::const_iterator;

 public:
  file_wrapper(const fs::path& path,
               std::size_t file_size,
               std::size_t block_size)
      : name_(path), file_size_(file_size), block_size_(block_size) {}

  bool operator==(const file_wrapper<T>& other) {
    auto current_iter = hashes_.begin();
    auto other_iter = other.hashes_.begin();
    std::ifstream in_this;
    std::ifstream in_other;

    // Поскольку в file_comparator все файлы лежат отсортированные по размеру,
    // то this.hashes_.size() == other.hashes_.size()
    while (has_next_block(current_iter) && has_next_block(other_iter)) {
      if (next_block(current_iter, in_this) !=
          next_block(other_iter, in_other)) {
        return false;
      }
    }
    return true;
  }

 private:
  // Проверка наличия блоков для сравнения.
  bool has_next_block(type_it it) {
    return not_complete() || it != hashes_.end();
  }

  bool not_complete() { return hashes_.size() * block_size_ < file_size_; }

  [[nodiscard]] const T& next_block(type_it it, std::ifstream& stream) {
    if (not_complete()) {
      std::vector<char> buffer(block_size_, 0);

      if (!stream.is_open()) {
        stream.open(name_, std::ios::binary);
      }

      stream.seekg(hashes_.size() * block_size_);
      stream.read(buffer.data(), block_size_);
      hashes_.push_back(calc_check_sum<T>(buffer.data(), block_size_));
      return hashes_.back();
    } else {
      assert(it != hashes_.end());
      return *it++;
    }
  }

  fs::path name_;           // путь до файла
  std::size_t file_size_;   // размер файла
  std::size_t block_size_;  // размер блока
  std::vector<T>
      hashes_;  // хеши блока в котором находится файл, либо мд5, либо crc32
};

}  // namespace bayan
