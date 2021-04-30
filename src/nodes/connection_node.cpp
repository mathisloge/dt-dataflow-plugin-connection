#include "connection_node.hpp"
namespace nodes
{
ConnectionNode::ConnectionNode(dt::df::core::IGraphManager &graph_manager,
                               const dt::df::NodeKey &key,
                               const std::string &title)
    : BaseNode(graph_manager, key, title)
    , io_ctx_{nullptr}
{}

void ConnectionNode::init(dt::df::core::IGraphManager &graph_manager)
{
    rx_data_slot_ = std::static_pointer_cast<DataOutT>(addOutput(graph_manager, "ByteArraySlot", "data", 0));
    on_data_slot_ = addCustomOutputFlow(graph_manager, "onDataReceived", 1);
    std::static_pointer_cast<dt::df::core::BaseSlot<IoCtxT>>(addInput(graph_manager, "AsioIoContext", "io-context", 0))
        ->connectToNodeFnc([this](auto io_ctx) {
            io_ctx_ = io_ctx;
            handleIoContextChange();
        });
}
} // namespace nodes
