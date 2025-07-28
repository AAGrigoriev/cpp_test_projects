#include "database.hpp"

#include <assert.h>

namespace db {

db_result database::insert(const std::string& table_id,
                           std::size_t id,
                           std::string& field) {
  if (!tables_.contains(table_id)) {
    return db_result(make_error_code(db_errc::wrong_table_error), table_id);
  }

  return tables_[table_id].insert(id, field);
}

db_result database::truncate(const std::string& table_id) {
  if (!tables_.contains(table_id)) {
    return db_result(make_error_code(db_errc::wrong_table_error), table_id);
  }

  tables_[table_id].truncate();
  return {std::error_code(), "OK"};
}

std::string database::intersect() const {
  assert(tables_.size() == 2);

  const auto& first_table = tables_.begin()->second;
  const auto& second_table = tables_.rbegin()->second;

  return intersect_impl(first_table, second_table);
}

std::string database::symmetric_difference() const {
  assert(tables_.size() == 2);

  const auto& first_table = tables_.begin()->second;
  const auto& second_table = tables_.rbegin()->second;

  return symmetric_difference_impl(first_table, second_table);
}

}  // namespace db
