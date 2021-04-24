#include "data_viewer_node.hpp"
#include <dt/df/core/graph_manager.hpp>
#include <dt/df/core/span_slot.hpp>
namespace nodes
{

static dt::df::Slots createInputs(dt::df::IGraphManager &graph_manager);
static dt::df::Slots createOutputs(dt::df::IGraphManager &graph_manager);

DataViewerNode::DataViewerNode(dt::df::IGraphManager &graph_manager)
    : WindowNode(graph_manager, kKey, kName, kName, createInputs(graph_manager), createOutputs(graph_manager))
{}
DataViewerNode::DataViewerNode(dt::df::IGraphManager &graph_manager, const nlohmann::json &json)
    : WindowNode(graph_manager, json)
{}

void DataViewerNode::addData(std::span<uint8_t> data)
{}
void DataViewerNode::drawWindow()
{
    if (ImGui::Button("Clear"))
    {
        data_.clear();
    }
    ImGui::SameLine();
    ImGui::Checkbox("Autoscroll", &auto_scroll_);
    // ImGui::PushFont(gFonts["Monospace"]);
    if (auto_scroll_)
    {
        mem_edit_.GotoAddr = data_.size() == 0 ? 0 : data_.size() - 1;
    }
    mem_edit_.DrawContents(data_.size() == 0 ? nullptr : &data_[0], data_.size());
    // ImGui::PopFont();
}

dt::df::Slots createInputs(dt::df::IGraphManager &graph_manager)
{
    dt::df::Slots inputs;
    try
    {
        const auto &span_fac = graph_manager.getSlotFactory("SpanSlot");
        inputs.emplace_back(
            span_fac(graph_manager, dt::df::SlotType::input, "data", 1, dt::df::SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return inputs;
}
dt::df::Slots createOutputs(dt::df::IGraphManager &graph_manager)
{
    return {};
}
} // namespace nodes
