#include "data_viewer_node.hpp"
#include <dt/df/core/graph_manager.hpp>
namespace nodes
{

DataViewerNode::DataViewerNode(dt::df::core::IGraphManager &graph_manager)
    : WindowBaseNode(graph_manager, kKey, kName, kName)
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

} // namespace nodes
