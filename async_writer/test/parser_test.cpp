#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "parser.hpp"

TEST(parser, static_command) {
  const auto result = async::parser().parse_command("1\n2\n3\n4\n5\n6\n");
  ASSERT_EQ(result.size(), 6);
  const auto test_result =
      std::vector<std::string>{"1", "2", "3", "4", "5", "6"};
  ASSERT_EQ(result, test_result);
}

TEST(parser, dinamic_command) {
  const auto result =
      async::parser().parse_command("abc\n{\nabc\ndef\n}\nbla\n");
  ASSERT_EQ(result.size(), 6);
  const auto test_result =
      std::vector<std::string>{"abc", "{", "abc", "def", "}", "bla"};
  ASSERT_EQ(result, test_result);
}
