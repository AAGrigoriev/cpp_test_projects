#pragma once

#include <map>
#include <shared_mutex>
#include <string>
#include <string_view>

#include "database_error.hpp"

namespace db {

class table {
 public:
  db_result insert(std::size_t id, std::string_view name);
  void truncate();
  friend std::string intersect_impl(const table& left, const table& right);
  friend std::string symmetric_difference_impl(const table& left,
                                               const table& right);

 private:
  std::map<std::size_t, std::string> table_;
  mutable std::shared_mutex mutex_;
};

}  // namespace db
