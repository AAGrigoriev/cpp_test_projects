#include "../table.hpp"

#include <string>
#include <system_error>

#include <gtest/gtest.h>

TEST(operation, insert) {
  db::table table;
  for (auto id = 0; id < 6; id++) {
    ASSERT_EQ(table.insert(id, std::to_string(id)).code, std::error_code{});
  }

  ASSERT_TRUE(table.insert(0, std::to_string(0)).code);
}

void fill_table_a(db::table& to_fill) {
  to_fill.insert(0, "lean");
  to_fill.insert(1, "sweater");
  to_fill.insert(2, "frank");
  to_fill.insert(3, "violation");
  to_fill.insert(4, "quality");
  to_fill.insert(5, "precision");
}

void fill_table_b(db::table& to_fill) {
  to_fill.insert(3, "proposal");
  to_fill.insert(4, "example");
  to_fill.insert(5, "lake");
  to_fill.insert(6, "flour");
  to_fill.insert(7, "wonder");
  to_fill.insert(8, "selection");
}

TEST(operation, truncate) {
  db::table a;
  fill_table_a(a);

  a.truncate();
  auto intersect_result = intersect_impl(a, a);
  auto sym_diff_result = symmetric_difference_impl(a, a);

  ASSERT_EQ(intersect_result.size(), 0UL);
  ASSERT_EQ(sym_diff_result.size(), 0UL);
}

TEST(operation, intersect) {
  db::table a;
  db::table b;

  fill_table_a(a);
  fill_table_b(b);

  auto testing_result = intersect_impl(a, b);
  std::string expected_result =
      "3,violation,proposal\n"
      "4,quality,example\n"
      "5,precision,lake\n";
  ASSERT_EQ(testing_result, expected_result);
}

TEST(operation, symmetric_difference) {
  db::table a;
  db::table b;

  fill_table_a(a);
  fill_table_b(b);

  auto testing_result = symmetric_difference_impl(a, b);
  std::string expected_result =
      "0,lean\n"
      "1,sweater\n"
      "2,frank\n"
      "6,flour\n"
      "7,wonder\n"
      "8,selection\n";
  ASSERT_EQ(testing_result, expected_result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
