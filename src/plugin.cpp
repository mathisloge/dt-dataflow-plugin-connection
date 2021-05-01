#include <Corrade/PluginManager/AbstractManager.h>
#include <Magnum/GL/OpenGL.h>
#include <Magnum/Platform/GLContext.h>
#include <dt/df/plugin/helper.hpp>
#include <dt/df/plugin/plugin.hpp>
#include <imnodes.h>
#include "connections/serial_connection.hpp"
#include "nodes/data_viewer_node.hpp"
#include "nodes/serial_node.hpp"
#include "nodes/serial_options_node.hpp"
#include "nodes/udp_node.hpp"
#include "nodes/udp_options_node.hpp"

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
        registerNode<nodes::SerialNode>(graph, "connections/con/");
        registerNode<nodes::SerialOptionsNode>(graph, "connections/opts/");
        registerNode<nodes::UdpNode>(graph, "connections/con/");
        registerNode<nodes::UdpOptionsNode>(graph, "connections/opts/");
    }
    void registerSlotFactories(core::IGraphManager &graph)
    {
        registerBaseSlot<const connection::SerialOptions &>(graph, "ConSerialOptions");
        registerBaseSlot<const connection::UdpOptions &>(graph, "ConUdpOptions");
    }
};
} // namespace dt::df::plugin

CORRADE_PLUGIN_REGISTER(ConnectionPlugin, dt::df::plugin::ConnectionPlugin, "de.mathisloge.dt.dataflow/1.0")
