#include "io_context_node.hpp"
#include <dt/df/core/graph_manager.hpp>

namespace nodes
{
static dt::df::Slots createInputs(dt::df::IGraphManager &graph_manager);
static dt::df::Slots createOutputs(dt::df::IGraphManager &graph_manager);

IoContextNode::IoContextNode(dt::df::IGraphManager &graph_manager)
    : BaseNode(graph_manager, kKey, kName, createInputs(graph_manager), createOutputs(graph_manager))
    , io_ctx_{nullptr}
    , should_run_{true}
{
    init();
}
IoContextNode::IoContextNode(dt::df::IGraphManager &graph_manager, const nlohmann::json &json)
    : BaseNode(graph_manager, json)
    , io_ctx_{nullptr}
    , should_run_{true}
{
    init();
}

void IoContextNode::init()
{
    io_ctx_ = std::make_shared<boost::asio::io_context>();
    std::static_pointer_cast<slots::IoContextSlot>(outputByLocalId(0))->setContext(io_ctx_);
}

void IoContextNode::calculate()
{}

void IoContextNode::runIoCtx()
{
    while (should_run_)
    {
        while (!io_ctx_)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        io_ctx_->run();
        // sleep. sometimes not sleeping will cause some problems (asio won't run correctly)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void IoContextNode::stop()
{
    should_run_ = false;
    if (io_ctx_)
    {
        io_ctx_->stop();
    }
    if (io_thread_.joinable())
        io_thread_.join();
}

IoContextNode::~IoContextNode()
{
    stop();
}

dt::df::Slots createInputs(dt::df::IGraphManager &)
{
    return {};
}
dt::df::Slots createOutputs(dt::df::IGraphManager &graph_manager)
{
    dt::df::Slots outputs;
    try
    {
        const auto &slot_fac = graph_manager.getSlotFactory(slots::IoContextSlot::kKey);
        outputs.emplace_back(
            slot_fac(graph_manager, dt::df::SlotType::output, "io_context", 0, dt::df::SlotFieldVisibility::never));
    }
    catch (...)
    {}
    return outputs;
}

} // namespace nodes
