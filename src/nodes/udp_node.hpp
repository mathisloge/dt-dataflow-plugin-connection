#pragma once
#include "../connections/udp_connection.hpp"
#include "connection_node.hpp"

namespace nodes
{
class UdpNode final: public ConnectionNode<connection::UdpOptions>
{
  public:
    static constexpr const char *kKey = "UdpConnectionNode";
    static constexpr const char *kName = "UDP-Connection";

  public:
    explicit UdpNode(dt::df::core::IGraphManager &graph_manager);
    void init(dt::df::core::IGraphManager &graph_manager) override;
    void evaluate() override;
    void processData(std::span<uint8_t> data) override;
    ~UdpNode();

  private:
    void handleIoContextChange() override;
    void handleIoOptionChange(const connection::UdpOptions& newopts) override;
    void handleDataInput(std::span<uint8_t> write_data) override;

  private:
    std::unique_ptr<connection::Udp> con_;
};
} // namespace nodes
