#pragma once
#include <thread>
#include <boost/asio.hpp>
#include <dt/df/core/base_node.hpp>
#include "../slots/io_context_slot.hpp"
namespace nodes
{
class IoContextNode final : public dt::df::BaseNode
{
  public:
    static constexpr const char *kKey = "IoContextNode";
    static constexpr const char *kName = "IoContext";

  public:
    IoContextNode(dt::df::IGraphManager &graph_manager);
    IoContextNode(dt::df::IGraphManager &graph_manager, const nlohmann::json &json);
    void calculate() override;

    ~IoContextNode();

  private:
    void init();
    void runIoCtx();
    void stop();

  private:
    bool should_run_;
    std::shared_ptr<boost::asio::io_context> io_ctx_;
    std::thread io_thread_;
};
} // namespace nodes
