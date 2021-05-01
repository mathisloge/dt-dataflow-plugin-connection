#pragma once
#include <span>
#include <vector>
#include <dt/df/core/window_base_node.hpp>
#include <imgui.h>
#include <imgui_memory_editor.h>
namespace nodes
{
class DataViewerNode : public dt::df::core::WindowBaseNode
{
  public:
    static constexpr const char *kKey = "ConnectionDataViewerNode";
    static constexpr const char *kName = "DataViewer";

  public:
    explicit DataViewerNode(dt::df::core::IGraphManager &graph_manager);
    void init(dt::df::core::IGraphManager &graph_manager) override;
    void addData(std::span<uint8_t> data);

  private:
    void drawWindow() override;

  private:
    MemoryEditor mem_edit_;
    bool auto_scroll_;
    std::vector<uint8_t> data_;
};
} // namespace nodes
