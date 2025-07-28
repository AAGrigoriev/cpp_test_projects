#include "mask.hpp"

#include <gtest/gtest.h>

using namespace testing;
using namespace bayan;

TEST(mask, main) {
  ASSERT_TRUE(mask("a").is_valid("a"));
  ASSERT_FALSE(mask("a").is_valid("b"));
  ASSERT_TRUE(mask("a*").is_valid("a"));
  ASSERT_FALSE(mask("a?").is_valid("a"));
  ASSERT_TRUE(mask("a?").is_valid("ab"));
  ASSERT_TRUE(mask("*b").is_valid("ab"));
  ASSERT_TRUE(mask("a*b").is_valid("acb"));
  ASSERT_TRUE(mask("a*b").is_valid("abc"));
  ASSERT_TRUE(mask("a.b").is_valid("a.b"));
  ASSERT_TRUE(mask(".b").is_valid(".b"));
  ASSERT_TRUE(mask("a.").is_valid("a."));
  ASSERT_TRUE(mask("*.*").is_valid("blabla.bla"));
}

TEST(mask, case_insensitive) {
  ASSERT_TRUE(mask("aBcDe").is_valid("AbCdE"));
  ASSERT_TRUE(mask("a*b").is_valid("AwErTyb"));
  ASSERT_TRUE(mask("a?").is_valid("AB"));
}
