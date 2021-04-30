#include "serial_node.hpp"
#include <dt/df/core/base_slot.hpp>
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
    std::dynamic_pointer_cast<dt::df::core::BaseSlot<const connection::SerialOptions &>>(
        addInput(graph_manager, "ConSerialOptions", "options", 1))
        ->connectToNodeFnc([this](const auto &opts) { options_ = opts; });
}

void SerialNode::handleIoContextChange()
{}

SerialNode::~SerialNode()
{}
} // namespace nodes
