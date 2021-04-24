#include "serial_node.hpp"
#include <dt/df/core/graph_manager.hpp>

namespace nodes
{
static dt::df::Slots createInputs(dt::df::IGraphManager &graph_manager);
static dt::df::Slots createOutputs(dt::df::IGraphManager &graph_manager);

SerialNode::SerialNode(dt::df::IGraphManager &graph_manager)
    : ConnectionNode(graph_manager, kKey, kName, createInputs(graph_manager), createOutputs(graph_manager))
{}
SerialNode::SerialNode(dt::df::IGraphManager &graph_manager, const nlohmann::json &json)
    : ConnectionNode(graph_manager, json)
{}
void SerialNode::calculate()
{}

void SerialNode::processData(std::span<uint8_t> data)
{
    rx_data_slot_->setValue(data);
}

void SerialNode::init()
{
    std::static_pointer_cast<slots::IoContextSlot>(inputByLocalId(0))->subscribe([this](const dt::df::BaseSlot *slot) {
        auto ioctx = static_cast<const slots::IoContextSlot *>(slot)->value();
        if (!ioctx)
        {
            serial_con_ = nullptr;
        }
        else
        {
            serial_con_ = std::make_shared<connection::Serial>(*this, *ioctx, "SerialNodeCon");
        }
    });
    rx_data_slot_ = std::static_pointer_cast<dt::df::SpanSlot>(outputByLocalId(0));
}

SerialNode::~SerialNode()
{}

dt::df::Slots createInputs(dt::df::IGraphManager &graph_manager)
{
    dt::df::Slots inputs;
    try
    {
        const auto &io_ctx_fac = graph_manager.getSlotFactory(slots::IoContextSlot::kKey);
        const auto &span_fac = graph_manager.getSlotFactory("SpanSlot");
        inputs.emplace_back(
            io_ctx_fac(graph_manager, dt::df::SlotType::input, "io_context", 0, dt::df::SlotFieldVisibility::never));
        inputs.emplace_back(
            span_fac(graph_manager, dt::df::SlotType::input, "send data", 1, dt::df::SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return inputs;
}
dt::df::Slots createOutputs(dt::df::IGraphManager &graph_manager)
{
    dt::df::Slots outputs;
    try
    {
        const auto &span_fac = graph_manager.getSlotFactory("SpanSlot");
        outputs.emplace_back(
            span_fac(graph_manager, dt::df::SlotType::output, "received data", 0, dt::df::SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return outputs;
}

} // namespace nodes
