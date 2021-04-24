#pragma once
#include "../connections/serial_connection.hpp"
#include "connection_node.hpp"

namespace nodes
{
class SerialNode : public ConnectionNode
{

  private:
    std::shared_ptr<connection::Serial> serial_con_;
};
} // namespace nodes
