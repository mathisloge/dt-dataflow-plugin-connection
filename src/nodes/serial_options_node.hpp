#pragma once
#include <dt/df/helper/simple_output_node.hpp>
#include "../connections/serial_connection.hpp"
namespace nodes
{
class SerialOptionsNode : public dt::df::SimpleOutputNode<connection::SerialOptions>
{
  public:
    static constexpr const char *kKey = "SerialOptionsNode";
    static constexpr const char *kName = "SerialOptions";

    explicit SerialOptionsNode(dt::df::core::IGraphManager &graph_manager);
    void init(dt::df::core::IGraphManager &graph_manager) override;
};
} // namespace nodes
