#pragma once

#include <string>
#include <system_error>

enum class db_errc {
  failed_to_parse_command,
  duplicate_error,
  wrong_table_error,
  unknow_error
};

namespace std {
template <>
struct is_error_code_enum<db_errc> : true_type {};
}  // namespace std

struct db_result {
  std::error_code code;
  std::string string;
};

std::error_code make_error_code(db_errc);
