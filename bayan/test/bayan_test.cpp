#include "com_parser.hpp"
#include "dir_parser.hpp"
#include "file_dublicate_parser.hpp"
#include "options.hpp"

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace testing;

class Bayan_Test : public ::testing::Test {
 protected:
  std::vector<std::vector<std::string>> Run(
      const std::vector<std::string>& a_arguments) {
    std::vector<std::string> arguments{a_arguments};
    std::vector<char*> argv;

    for (const auto& arg : arguments) {
      argv.push_back((char*)arg.data());
    }

    argv.push_back(nullptr);

    bayan::command_parser command_parser(argv.size() - 1, argv.data());
    auto options = command_parser.parse_data();

    bayan::dir_parser dir_parser(std::move(options.value().dir_opt));
    auto groupPath = dir_parser.get_group_path();

    bayan::file_dublicate_parser dup_parser(
        std::move(options.value().hash_opt));
    const auto duplicates = dup_parser.scan_dublicate(groupPath);

    std::vector<std::vector<std::string>> result;
    for (auto& dup : duplicates) {
      std::vector<std::string> fileNames;
      for (auto& path : dup) {
        fileNames.emplace_back(path.filename().string());
      }
      result.emplace_back(fileNames);
    }

    return result;
  }
};

TEST_F(Bayan_Test, Test_1_Simple) {
  auto result = Run({"bayan", "-idata/test_1/", "-m*.cpp", "-m*.txt"});
  ASSERT_EQ(result.size(), (std::size_t)2);
  ASSERT_EQ(result[0].size(), (std::size_t)2);
  ASSERT_EQ(result[1].size(), (std::size_t)2);
}

TEST_F(Bayan_Test, Test_1_Masks) {
  auto result = Run({"bayan", "-idata/test_1/", "-m*.cpp"});
  ASSERT_EQ(result.size(), (std::size_t)1);
  ASSERT_EQ(result[0].size(), (std::size_t)2);
  ASSERT_THAT(result[0],
              ElementsAre(StrEq("hello_copy.cpp"), StrEq("hello.cpp")));
}

TEST_F(Bayan_Test, Test_1_Size) {
  auto result = Run({"bayan", "-idata/test_1/", "-s100", "-m*.cpp", "-m*.txt"});
  ASSERT_EQ(result.size(), (std::size_t)1);
  ASSERT_EQ(result[0].size(), (std::size_t)2);
  ASSERT_THAT(result[0],
              ElementsAre(StrEq("hello_copy.cpp"), StrEq("hello.cpp")));
}

TEST_F(Bayan_Test, Test_2_Level) {
  auto result = Run({"bayan", "-idata/test_2", "-r1", "-m*.cpp", "-m*.txt"});
  ASSERT_EQ(result.size(), (std::size_t)2);
  ASSERT_EQ(result[0].size(), (std::size_t)2);
  ASSERT_EQ(result[1].size(), (std::size_t)2);
  // EXPECT_THAT(result[0], ElementsAre( StrEq("hello_copy.cpp"),
  // StrEq("hello.cpp") )); EXPECT_THAT(result[1], ElementsAre(
  // StrEq("just_single_file_copy.doc"), StrEq("just_single_file.doc")));
}

TEST_F(Bayan_Test, Test_2_Exclude) {
  auto result = Run({"bayan", "-idata/test_2/", "-edata/test_2/level_1/", "-r1",
                     "-m*.cpp", "-m*.txt"});
  ASSERT_EQ(result.size(), (std::size_t)1);
  ASSERT_EQ(result[0].size(), (std::size_t)2);
  ASSERT_THAT(result[0],
              ElementsAre(StrEq("hello_copy.cpp"), StrEq("hello.cpp")));
}

TEST_F(Bayan_Test, Test_3_Multi) {
  auto result = Run({"bayan", "-idata/test_3/", "-r1", "-m*.cpp", "-m*.txt"});
  ASSERT_EQ(result.size(), (std::size_t)1);
  ASSERT_EQ(result[0].size(), (std::size_t)3);
  // EXPECT_THAT(result[0], ElementsAre( StrEq("file3.txt"), StrEq("file1.txt"),
  // StrEq("file2.txt") ));
}
