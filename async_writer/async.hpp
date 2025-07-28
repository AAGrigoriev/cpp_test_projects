#pragma once

#include "context.hpp"

#include <string>

namespace async {

context* connect();

/*!
 * Reads commands from the buffer and enqueues them for asynchronous processing.
 * Performs some amount of processing.
 * Does not guarantee all enqueued commands being processed upon function
 * return. The remaining commands are guaranteed be processed later;
 */
void receive(context* context, const std::string& data, std::size_t bulk_size);

void disconnect(context*);

}  // namespace async
