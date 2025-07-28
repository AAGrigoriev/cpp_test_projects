#include "table.hpp"

#include <algorithm>
#include <mutex>
#include <sstream>

#include "database_error.hpp"

namespace db {

constexpr std::string_view comma_token = ",";
constexpr std::string_view newline_token = "\n";

db_result table::insert(std::size_t id, std::string_view field) {
  std::unique_lock _(mutex_);
  auto result = table_.try_emplace(id, field);

  return result.second
             ? db_result{std::error_code{}, "OK"}
             : db_result{make_error_code(db_errc::duplicate_error), ""};
}

void table::truncate() {
  std::unique_lock _(mutex_);
  table_.clear();
}

std::string intersect_impl(const table& left, const table& right) {
  std::stringstream result;

  std::shared_lock left_lock(left.mutex_, std::defer_lock);
  std::shared_lock right_lock(right.mutex_, std::defer_lock);
  std::lock(left_lock, right_lock);

  auto left_beg = left.table_.begin();
  auto right_beg = right.table_.begin();

  while (left_beg != left.table_.end() && right_beg != right.table_.end()) {
    if (*left_beg < *right_beg) {  // false -> right <= left
      ++left_beg;
    } else {
      if (!(*right_beg < *left_beg)) {
        result << left_beg->first << comma_token << left_beg->second
               << comma_token << right_beg->second << newline_token;
        ++left_beg;
      }
      ++right_beg;
    }
  }

  return result.str();
}

std::string symmetric_difference_impl(const table& left, const table& right) {
  std::stringstream result;

  std::shared_lock left_lock(left.mutex_, std::defer_lock);
  std::shared_lock right_lock(right.mutex_, std::defer_lock);
  std::lock(left_lock, right_lock);

  auto left_beg = left.table_.begin();
  auto right_beg = right.table_.begin();

  while (left_beg != right_beg) {
    if (right_beg == right.table_.end()) {
      std::for_each(left_beg, left.table_.end(), [&result](const auto& pair) {
        result << pair.first << comma_token << pair.second << newline_token;
      });
      return result.str();
    }

    if (*left_beg < *right_beg) {
      result << left_beg->first << comma_token << left_beg->second
             << newline_token;
      ++left_beg;
    } else {
      if (*right_beg < *left_beg) {
        result << right_beg->first << comma_token << right_beg->second
               << newline_token;
      } else {
        ++left_beg;
      }
      ++right_beg;
    }
  }

  std::for_each(right_beg, right.table_.end(), [&result](const auto& pair) {
    result << pair.first << comma_token << pair.second << newline_token;
  });

  return result.str();
}

}  // namespace db
