#include <gtest/gtest.h>

#include <vector>

#include "controller.hpp"

auto create_controller(std::size_t bulk_size) {
  async::s_command_queue logging_queue =
      std::make_shared<async::notifying_queue<async::s_command>>();
  async::s_command_queue output_queue =
      std::make_shared<async::notifying_queue<async::s_command>>();
  async::controller controller(logging_queue, output_queue);
  controller.set_bulk_size(bulk_size);
  return controller;
}

TEST(controller, simple_command) {
  using namespace std::string_literals;

  // todo : fixtures
  async::s_command_queue logging_queue =
      std::make_shared<async::notifying_queue<async::s_command>>();
  async::s_command_queue output_queue =
      std::make_shared<async::notifying_queue<async::s_command>>();
  async::controller controller(logging_queue, output_queue);
  controller.set_bulk_size(3);

  std::vector<std::string> input_data{"123", "456", "789"};
  async::command expected_result(std::vector<std::string>{"123", "456", "789"},
                                 {});

  controller.process_command(std::move(input_data));

  auto logging_result = logging_queue->get_queue();
  auto output_result = output_queue->get_queue();
  ASSERT_EQ(logging_result.size(), 1);
  ASSERT_EQ(output_result.size(), 1);

  ASSERT_EQ(logging_result.front()->commands_, expected_result.commands_);
  ASSERT_EQ(output_result.front()->commands_, expected_result.commands_);
}

TEST(controller, dinamic_command) {
  using namespace std::string_literals;

  // todo : fixtures
  async::s_command_queue logging_queue =
      std::make_shared<async::notifying_queue<async::s_command>>();
  async::s_command_queue output_queue =
      std::make_shared<async::notifying_queue<async::s_command>>();
  async::controller controller(logging_queue, output_queue);
  controller.set_bulk_size(3);

  std::vector<std::string> input_data{"123", "456", "{",   "000",
                                      "111", "}",   "222", "333"};

  std::queue<async::command> expected_result;
  expected_result.push(async::command({"123", "456"}, {}));
  expected_result.push(async::command({"000", "111"}, {}));
  expected_result.push(async::command({"222", "333"}, {}));

  controller.process_command(std::move(input_data));

  auto logging_result = logging_queue->get_queue();
  auto output_result = output_queue->get_queue();
  ASSERT_EQ(logging_result.size(), 3);
  ASSERT_EQ(output_result.size(), 3);

  ASSERT_EQ(logging_result.size(), expected_result.size());
  ASSERT_EQ(output_result.size(), expected_result.size());

  while (!logging_result.empty() && !output_result.empty() &&
         !expected_result.empty()) {
    auto s_l = logging_result.front();
    auto s_o = output_result.front();
    auto s_e = std::move(expected_result.front());
    logging_result.pop();
    output_result.pop();
    expected_result.pop();
    ASSERT_EQ(s_l->commands_, s_e.commands_);
    ASSERT_EQ(s_o->commands_, s_e.commands_);
  }
}
