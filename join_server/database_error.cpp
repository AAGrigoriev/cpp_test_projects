#include "database_error.hpp"

namespace {

struct db_err_category : std::error_category {
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

const char* db_err_category::name() const noexcept {
  return "db error";
}

std::string db_err_category::message(int v) const {
  switch (static_cast<db_errc>(v)) {
    case db_errc::failed_to_parse_command:
      return "ERR failed to parse command\n";
    case db_errc::duplicate_error:
      return "ERR duplicate";
    case db_errc::wrong_table_error:
      return "ERR wrong_table";
    case db_errc::unknow_error:
      return "ERR unknow";
  }
}

const auto& create_category() {
  const static db_err_category db_err_category_;
  return db_err_category_;
}

}  // namespace

std::error_code make_error_code(db_errc e) {
  return {static_cast<int>(e), create_category()};
}
