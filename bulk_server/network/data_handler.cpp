#include "data_handler.hpp"

#include "global_context.hpp"

namespace network {

data_handler::data_handler(std::size_t bulk_size)
    : controller_(logic::global_context::get_instance(bulk_size)) {}

}  // namespace network
