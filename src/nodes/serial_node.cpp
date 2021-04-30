#include "serial_node.hpp"
namespace nodes
{

SerialNode::SerialNode(dt::df::core::IGraphManager &graph_manager)
    : ConnectionNode(graph_manager, std::string{kKey}, std::string{kName})
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

void SerialNode::handleIoContextChange()
{
}

SerialNode::~SerialNode()
{}
} // namespace nodes
