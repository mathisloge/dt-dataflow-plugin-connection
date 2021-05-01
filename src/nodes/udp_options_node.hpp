#pragma once
#include <dt/df/helper/simple_output_node.hpp>
#include "../connections/udp_connection.hpp"
namespace nodes
{
class UdpOptionsNode final : public dt::df::SimpleOutputNode<connection::UdpOptions>
{
  public:
    static constexpr const char *kKey = "UdpOptionsNode";
    static constexpr const char *kName = "UdpOptions";

    explicit UdpOptionsNode(dt::df::core::IGraphManager &graph_manager);
    void init(dt::df::core::IGraphManager &graph_manager) override;

  private:
    void renderCustomContent() override;
};
} // namespace nodes
