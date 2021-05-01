#pragma once
#include "../connections/tcp_connection.hpp"
#include "connection_node.hpp"
namespace nodes
{
class TcpClientNode : public ConnectionNode<connection::TcpOptions>
{};
} // namespace nodes
