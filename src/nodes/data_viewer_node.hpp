#pragma once
#include <span>
#include <vector>
#include <dt/df/core/window_node.hpp>
#include <imgui.h>
#include <imgui_memory_editor.h>
namespace nodes
{
class DataViewerNode : public dt::df::WindowNode
{
  public:
    static constexpr const char *kKey = "ConnectionDataViewerNode";
    static constexpr const char *kName = "DataViewer";

  public:
    DataViewerNode(dt::df::IGraphManager &graph_manager);
    DataViewerNode(dt::df::IGraphManager &graph_manager, const nlohmann::json &json);
    void addData(std::span<uint8_t> data);

  private:
    void drawWindow() override;

  private:
    MemoryEditor mem_edit_;
    bool auto_scroll_;
    std::vector<uint8_t> data_;
};
} // namespace nodes
