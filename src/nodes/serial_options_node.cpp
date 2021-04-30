#include "serial_options_node.hpp"
namespace nodes
{
SerialOptionsNode::SerialOptionsNode(dt::df::core::IGraphManager &graph_manager)
    : SimpleOutputNode<connection::SerialOptions>(graph_manager, std::string{kKey}, std::string{kName})
{}
void SerialOptionsNode::init(dt::df::core::IGraphManager &graph_manager)
{
    output_slot_ = registerOutput(graph_manager, "ConSerialOptions", "options", 0);
}
} // namespace nodes
