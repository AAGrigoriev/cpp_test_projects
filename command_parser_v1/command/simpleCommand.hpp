#pragma once

#include <vector>
#include <string>
#include <chrono>

namespace Reader {
struct Command {
   void put_command(std::string &&command);

   std::string getTime() const;

   void clearCommand();

   std::vector<std::string> const &getCommand() const;

private:
   std::chrono::system_clock::time_point time_point;
   std::vector<std::string> stringCommand;
};
} // namespace fileReader
