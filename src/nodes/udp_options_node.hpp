#pragma once
#include <dt/df/helper/simple_output_node.hpp>
#include "../connections/udp_connection.hpp"
namespace nodes
{
class UdpOptionsNode final : public dt::df::SimpleOutputNode<UdpOptionsNode, connection::UdpOptions>
{
  public:
    static constexpr const char *kKey = "UdpOptionsNode";
    static constexpr const char *kName = "UdpOptions";
    static constexpr const char *kSlotOutKey = "ConUdpOptions";
    static constexpr const char *kSlotOutName = "options";
    using SimpleOutputNode::SimpleOutputNode;

  private:
    void renderCustomContent() override;
};
} // namespace nodes
