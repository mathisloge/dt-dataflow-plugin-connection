#include <Corrade/PluginManager/AbstractManager.h>
#include <Magnum/GL/OpenGL.h>
#include <Magnum/Platform/GLContext.h>
#include <dt/df/plugin/plugin.hpp>
#include <imnodes.h>
#include "nodes/data_viewer_node.hpp"
#include "nodes/io_context_node.hpp"
#include "nodes/serial_node.hpp"
#include "slots/io_context_slot.hpp"
namespace dt::df::plugin
{

template <typename TSlot>
void registerSlot(IGraphManager &graph)
{
    graph.registerSlotFactory(
        TSlot::kKey,
        [](IGraphManager &graph, SlotType type, const SlotName &name, SlotId local, SlotFieldVisibility vis) {
            return std::make_shared<TSlot>(TSlot::kKey, graph, type, name, local, vis);
        },
        [](const nlohmann::json &json) { return std::make_shared<TSlot>(json); });
}

template <typename TNode>
void registerNode(IGraphManager &graph, const std::string &group)
{
    graph.registerNodeFactory(
        TNode::kKey,
        group + std::string{TNode::kName},
        [](IGraphManager &graph) { return std::make_shared<TNode>(graph); },
        [](IGraphManager &graph, const nlohmann::json &json) { return std::make_shared<TNode>(graph, json); });
}

class ConnectionPlugin final : public Plugin
{

  public:
    explicit ConnectionPlugin(Corrade::PluginManager::AbstractManager &manager, const std::string &plugin)
        : Plugin{manager, plugin}
    {}

    void setup(Magnum::GL::Context &gl_ctx, ImGuiContext *imgui_ctx, imnodes::Context *imnodes_ctx)
    {
        Magnum::Platform::GLContext::makeCurrent(&gl_ctx);
        ImGui::SetCurrentContext(imgui_ctx);
        imnodes::SetCurrentContext(imnodes_ctx);
    }
    void registerNodeFactories(IGraphManager &graph)
    {
        registerNode<nodes::DataViewerNode>(graph, "connections/");
        registerNode<nodes::SerialNode>(graph, "connections/");
        registerNode<nodes::IoContextNode>(graph, "connections/");
    }
    void registerSlotFactories(IGraphManager &graph)
    {
        registerSlot<slots::IoContextSlot>(graph);
    }
};
} // namespace dt::df::plugin

CORRADE_PLUGIN_REGISTER(ConnectionPlugin, dt::df::plugin::ConnectionPlugin, "de.mathisloge.dt.dataflow/1.0")
