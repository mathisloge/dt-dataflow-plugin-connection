#include <Corrade/PluginManager/AbstractManager.h>
#include <Magnum/GL/OpenGL.h>
#include <Magnum/Platform/GLContext.h>
#include <dt/df/plugin/helper.hpp>
#include <dt/df/plugin/plugin.hpp>
#include <imnodes.h>
#include "nodes/data_viewer_node.hpp"
#include "nodes/serial_node.hpp"
namespace dt::df::plugin
{
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
    void registerNodeFactories(core::IGraphManager &graph)
    {
        registerNode<nodes::DataViewerNode>(graph, "connections/");
        registerNode<nodes::SerialNode>(graph, "connections/");
    }
    void registerSlotFactories(core::IGraphManager &graph)
    {}
};
} // namespace dt::df::plugin

CORRADE_PLUGIN_REGISTER(ConnectionPlugin, dt::df::plugin::ConnectionPlugin, "de.mathisloge.dt.dataflow/1.0")
