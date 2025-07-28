#include "network.hpp"

#include <memory>

namespace nett {

server::server(boost::asio::io_context& context,
               const tcp::endpoint& endpoint,
               handler_t handler)
    : acceptor_(context, endpoint), handler_(std::move(handler)) {}

void server::do_accept() {
  acceptor_.async_accept(
      [this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
          auto session = session::create(std::move(socket), handler_);
        }
        do_accept();
      });
}

session::session_pointer session::create(tcp::socket&& socket,
                                         handler_t handler) {
  return session_pointer(new session(std::move(socket), std::move(handler)));
}

void session::start() {
  do_read();
}

session::session(tcp::socket socket, handler_t handler)
    : socket_(std::move(socket)), handler_(std::move(handler)) {}

void session::do_read() {
  auto self = shared_from_this();
  socket_.async_read_some(
      boost::asio::buffer(buffer_, buffer_.size()),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (ec) {
          return;
        }

        if (auto it = std::find(buffer_.rbegin(), buffer_.rend(), '\n');
            it != buffer_.rend()) {
          std::string result(std::move(temp_string_) +
                             std::string(buffer_.begin(), it.base()));
          temp_string_ = std::string(it.base() + 1, buffer_.end());
          auto res = handler_(result);
          do_write(res);
        } else {
          temp_string_.append(buffer_.begin(), buffer_.end());
          do_read();
        }
      });
}

void session::do_write(std::string_view data) {
  auto self(shared_from_this());
  socket_.async_send(boost::asio::buffer(data.data(), data.size()),
                     [this, self](boost::system::error_code ec, std::size_t) {
                       if (!ec) {
                         do_read();
                       }
                     });
}

}  // namespace nett
