#pragma once

#include <memory>

#include "command.hpp"
#include "notify_queue.hpp"

namespace async {

using s_command = std::shared_ptr<command>;
using s_command_queue = std::shared_ptr<notifying_queue<s_command>>;

}  // namespace async
