#pragma once
#include <optional>
#include <boost/asio.hpp>
#include <dt/df/core/base_node.hpp>
#include <dt/df/core/base_slot.hpp>
#include <dt/df/core/types.hpp>
#include "../connections/connection_handle.hpp"
namespace nodes
{
class ConnectionNode : public dt::df::core::BaseNode, public connection::ConnectionHandle
{
  public:
    using ByteArrayT = std::span<uint8_t>;
    using DataOutT = dt::df::core::BaseSlot<ByteArrayT>;
    using IoCtxT = std::shared_ptr<boost::asio::io_context>;
    explicit ConnectionNode(dt::df::core::IGraphManager &graph_manager,
                            const dt::df::NodeKey &key,
                            const std::string &title);

    virtual void init(dt::df::core::IGraphManager &graph_manager) override;

  protected:
    virtual void handleIoContextChange() = 0;

  protected:
    std::shared_ptr<DataOutT> rx_data_slot_;
    dt::df::SlotFlowPtr on_data_slot_;
    IoCtxT io_ctx_;
};
} // namespace nodes
