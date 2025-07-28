#pragma once

#include <memory>

#include "command.hpp"
#include "notify_queue.hpp"

namespace async {

using s_command = std::shared_ptr<command>;
using n_queue = notifying_queue<s_command>;
using s_command_queue = std::shared_ptr<n_queue>;

}  // namespace async
