#pragma once

#include <cstdint>

struct hash_key {
  std::size_t first, last;

  hash_key(std::size_t f, std::size_t l) : first(f), last(l) {}

  bool operator==(const hash_key& p) const {
    return first == p.first && last == p.last;
  }
};

class hash_functions {
 public:
  /*! @brief Pairing function
   *         https://en.wikipedia.org/wiki/Pairing_function
   */
  std::size_t operator()(const hash_key& p) const {
    return 0.5 * (p.first + p.last) * (p.first + p.last + 1) + p.last;
  }
};
