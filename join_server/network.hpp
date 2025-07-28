#pragma once

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <string_view>

#include <boost/asio.hpp>

namespace nett {

constexpr std::size_t MAX_PACKET_SIZE = 4096;

using boost::asio::ip::tcp;

using handler_t = std::function<std::string(std::string_view)>;

class server {
 public:
  server(boost::asio::io_context& context,
         const tcp::endpoint& endpoint,
         handler_t handler);

 private:
  void do_accept();

 private:
  tcp::acceptor acceptor_;
  handler_t handler_;
};

class session : std::enable_shared_from_this<session> {
 public:
  using session_pointer = std::shared_ptr<session>;

  static session_pointer create(tcp::socket&&, handler_t);

  void start();

 private:
  session(tcp::socket, handler_t);
  void do_read();
  void do_write(std::string_view data);

 private:
  tcp::socket socket_;
  handler_t handler_;
  std::array<char, MAX_PACKET_SIZE> buffer_;
  std::string temp_string_;
};

}  // namespace nett
