#include <gtest/gtest.h>
#include <sstream>

#include "console_writer.hpp"
#include "reader.hpp"

class TestReader : public ::testing::Test {
 protected:
  void SetUp(std::size_t bulk_count, std::istream& is, std::ostream& os) {
    reader_ = std::make_unique<Reader::Reader>(bulk_count, is);
    writer_ = std::make_shared<Reader::ConsoleWriter>(os);
    reader_->attach(writer_);
  }

  void TearDown() {
    reader_.reset(nullptr);
    writer_.reset();
  }
  std::unique_ptr<Reader::Reader> reader_;

 private:
  std::shared_ptr<Reader::ConsoleWriter> writer_;
};

TEST_F(TestReader, N_3) {
  std::stringstream input("cmd1\ncmd2\ncmd3");
  std::stringstream output;
  std::stringstream result("bulk : cmd1,cmd2,cmd3\n");

  SetUp(3, input, output);

  reader_->run();
  ASSERT_EQ(result.str(), output.str());
}

TEST_F(TestReader, dinamic_size) {
  std::stringstream input(
      "cmd1\ncmd2\n"
      "{"
      "\ncmd3\ncmd4\n"
      "}\n"
      "{\n"
      "cmd5\ncmd6\n"
      "{"
      "\ncmd7\ncmd8\n"
      "}"
      "\ncmd9\n"
      "}\n");
  std::stringstream output;
  std::stringstream result;
  result << "bulk : cmd1,cmd2" << std::endl;
  result << "bulk : cmd3,cmd4" << std::endl;
  result << "bulk : cmd5,cmd6,cmd7,cmd8,cmd9" << std::endl;

  SetUp(3, input, output);

  reader_->run();

  ASSERT_EQ(result.str(), output.str());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
