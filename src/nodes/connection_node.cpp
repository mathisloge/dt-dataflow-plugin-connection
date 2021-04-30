#include "connection_node.hpp"
namespace nodes
{

void ConnectionNode::init(dt::df::core::IGraphManager &graph_manager)
{
    rx_data_slot_ = std::static_pointer_cast<DataOutT>(addOutput(graph_manager, "ByteArraySlot", "data", 0));
    on_data_slot_ = addCustomOutputFlow(graph_manager, "onDataReceived", 1);
}
} // namespace nodes
