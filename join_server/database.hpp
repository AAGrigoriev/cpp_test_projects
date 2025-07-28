#pragma once

#include <cstddef>
#include <map>

#include "table.hpp"

namespace db {

class database {
 public:
  db_result insert(const std::string& table_id,
                   std::size_t id,
                   std::string& field);
  db_result truncate(const std::string& table_id);
  std::string intersect() const;
  std::string symmetric_difference() const;

 private:
  std::map<std::string, table> tables_;
};

}  // namespace db
