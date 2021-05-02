#pragma once
#include <dt/df/helper/simple_output_node.hpp>
#include "../connections/serial_connection.hpp"
namespace nodes
{
class SerialOptionsNode : public dt::df::SimpleOutputNode<SerialOptionsNode, connection::SerialOptions>
{
  public:
    static constexpr const char *kKey = "SerialOptionsNode";
    static constexpr const char *kName = "SerialOptions";
    static constexpr const char *kSlotOutKey = "ConSerialOptions";
    static constexpr const char *kSlotOutName = "options";
    using SimpleOutputNode::SimpleOutputNode;
};
} // namespace nodes
