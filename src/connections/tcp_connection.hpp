#pragma once
#include <memory>
#include <boost/asio.hpp>
#include "connection_handle.hpp"
#include "options.hpp"

namespace connection
{
struct TcpOptions : Options
{
    std::string server;
    unsigned short server_port;
    std::string service;
    char packet_end;
};

class Tcp final : public std::enable_shared_from_this<Tcp>
{
    using tcp = boost::asio::ip::tcp;

  public:
    static constexpr std::string_view kType = "tcp";

  public:
    explicit Tcp(ConnectionHandle &handle, boost::asio::io_context &io_context, const std::string &identifier);
    bool isConnected() const;
    void connect();
    void disconnect();
    void write(std::span<uint8_t> data);
    void applyOptions();
    void setOptions(const TcpOptions &opts);
    void setOption(const std::string &server, const unsigned short server_port, const std::string &service = "");
    void setOption(char packet_end);
    const Options &options() const;
    const TcpOptions &tcpOptions() const;
    std::string_view type() const;

  private:
    void beginConnect(tcp::resolver::results_type::iterator endpoint_iter);
    void handleConnect(const boost::system::error_code &error, tcp::resolver::results_type::iterator endpoint_iter);
    void startRead();
    void handleRead(const boost::system::error_code &error, std::size_t n);
    void handleWrite(std::shared_ptr<std::vector<uint8_t>> buffer_tx,
                     const boost::system::error_code &error,
                     std::size_t bytes_transferred);

  private:
    ConnectionHandle &handle_;
    /// Strand to ensure the connection's handlers are not called concurrently.
    boost::asio::strand<boost::asio::executor> strand_;
    std::vector<uint8_t> buffer_rx_;
    TcpOptions options_;

    tcp::socket socket_;
    tcp::resolver::results_type endpoints_;
    bool should_run_;

    bool is_connected_;
};
} // namespace connection
