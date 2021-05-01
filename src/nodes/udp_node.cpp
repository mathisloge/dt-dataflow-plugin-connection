#include "udp_node.hpp"
#include <dt/df/core/base_slot.hpp>
#include <spdlog/spdlog.h>
namespace nodes
{

UdpNode::UdpNode(dt::df::core::IGraphManager &graph_manager)
    : ConnectionNode(graph_manager, std::string{kKey}, std::string{kName})
    , con_{nullptr}
{}

void UdpNode::evaluate()
{}

void UdpNode::processData(std::span<uint8_t> data)
{
    rx_data_slot_->setValue(data);
}

void UdpNode::init(dt::df::core::IGraphManager &graph_manager)
{
    ConnectionNode::init(graph_manager);
    std::dynamic_pointer_cast<dt::df::core::BaseSlot<const connection::UdpOptions &>>(
        addInput(graph_manager, "ConUdpOptions", "options", 2))
        ->connectToNodeFnc([this](const auto &opts) { handleIoOptionChange(opts); });
}

void UdpNode::handleIoContextChange()
{
    if (io_ctx_)
    {
        SPDLOG_DEBUG("NEW CONNECTION");
        con_ = std::make_unique<connection::Udp>(*this, *io_ctx_, "myudp");
        con_->setOptions(options_);
        con_->applyOptions();
        con_->connect();
    }
    else
        con_ = nullptr;
}

void UdpNode::handleIoOptionChange(const connection::UdpOptions &newopts)
{
    SPDLOG_DEBUG("NEW OPTIONS");
    options_ = newopts;
    if (con_)
    {
        SPDLOG_DEBUG("APPLY OPTIONS");
        con_->setOptions(options_);
        con_->applyOptions();
    }
}

void UdpNode::handleDataInput(std::span<uint8_t> write_data)
{
    if (con_)
    {
        SPDLOG_DEBUG("SEND DATA: {}", write_data.size());
        con_->write(write_data);
    }
}

UdpNode::~UdpNode()
{}
} // namespace nodes
