#pragma once

#include <chrono>
#include <iostream>
#include <string>
#include <vector>


namespace async {

class command final {
public:
  void push_command(std::string&& command);

  const std::string& get_time() const;

  const std::vector<std::string>& get_command() const;

  void clear_command();

  bool empty() const;

  friend std::ostream &operator<<(std::ostream& a_osOut, const command& command);

private:
  std::vector<std::string> command_;
  std::string              time_;
};

} // namespace async