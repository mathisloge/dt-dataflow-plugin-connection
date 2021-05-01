#pragma once
#include <optional>
#include <boost/asio.hpp>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/base_slot.hpp>
#include <dt/df/core/types.hpp>
#include "../connections/connection_handle.hpp"
namespace nodes
{
template <typename TOpts>
class ConnectionNode : public dt::df::core::BaseNode, public connection::ConnectionHandle
{
  public:
    using ByteArrayT = std::span<uint8_t>;
    using DataOutT = dt::df::core::BaseSlot<ByteArrayT>;
    using IoCtxT = std::shared_ptr<boost::asio::io_context>;
    explicit ConnectionNode(dt::df::core::IGraphManager &graph_manager,
                            const dt::df::NodeKey &key,
                            const std::string &title)
        : BaseNode(graph_manager, key, title)
        , io_ctx_{nullptr}
    {}

    virtual void init(dt::df::core::IGraphManager &graph_manager) override
    {
        rx_data_slot_ = std::static_pointer_cast<DataOutT>(addOutput(graph_manager, "ByteArraySlot", "data", 0));
        on_data_slot_ = addCustomOutputFlow(graph_manager, "onDataReceived", 1);
        std::static_pointer_cast<dt::df::core::BaseSlot<IoCtxT>>(
            addInput(graph_manager, "AsioIoContext", "io-context", 0))
            ->connectToNodeFnc([this](auto io_ctx) {
                io_ctx_ = io_ctx;
                handleIoContextChange();
            });

        std::static_pointer_cast<DataOutT>(addInput(graph_manager, "ByteArraySlot", "write", 1))
            ->connectToNodeFnc(std::bind(&ConnectionNode::handleDataInput, this, std::placeholders::_1));
    }

  protected:
    virtual void handleIoContextChange() = 0;
    virtual void handleIoOptionChange(const TOpts &newopts) = 0;
    virtual void handleDataInput(std::span<uint8_t> write_data) = 0;

  protected:
    std::shared_ptr<DataOutT> rx_data_slot_;
    dt::df::SlotFlowPtr on_data_slot_;
    TOpts options_;
    IoCtxT io_ctx_;
};
} // namespace nodes
