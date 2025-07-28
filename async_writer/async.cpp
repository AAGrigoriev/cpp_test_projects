#include "async.hpp"

#include <assert.h>

namespace async {

context* connect() {
  return new context();
}

void receive(context* context, const std::string& data, std::size_t bulk_size) {
  assert(context);

  context->process_command(data, bulk_size);
}

void disconnect(context* context) {
  delete context;
}

}  // namespace async
