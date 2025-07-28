#include "session.hpp"

namespace network {

session::session(std::size_t bulk_size, asio::ip::tcp::socket&& socket)
    : socket_(std::move(socket)), data_handler_(bulk_size) {}

void session::start() {
  do_read();
}

void session::do_read() {
  auto self(shared_from_this());
  socket_.async_read_some(
      boost::asio::buffer(buffer_, BUFFER_SIZE),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          data_handler_.recieve(buffer_, length);
          do_read();
        }
      });
}

}  // namespace network
