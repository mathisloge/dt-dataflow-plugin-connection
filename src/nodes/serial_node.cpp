#include "serial_node.hpp"
namespace nodes
{

SerialNode::SerialNode(dt::df::core::IGraphManager &graph_manager)
    : ConnectionNode(graph_manager, kKey, kName)
{}

void SerialNode::evaluate()
{}

void SerialNode::processData(std::span<uint8_t> data)
{
    
    rx_data_slot_->setValue(data);
}

void SerialNode::init(dt::df::core::IGraphManager &graph_manager)
{
    ConnectionNode::init(graph_manager);
}

SerialNode::~SerialNode()
{}
} // namespace nodes
