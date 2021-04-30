#pragma once
#include <dt/df/core/base_slot.hpp>
#include "../connections/serial_connection.hpp"
#include "connection_node.hpp"
namespace nodes
{
class SerialNode final : public ConnectionNode
{
  public:
    static constexpr const char *kKey = "SerialConnectionNode";
    static constexpr const char *kName = "SerialConnection";

  public:
    explicit SerialNode(dt::df::core::IGraphManager &graph_manager);
    void init(dt::df::core::IGraphManager &graph_manager) override;
    void evaluate() override;
    void processData(std::span<uint8_t> data) override;
    ~SerialNode();

  private:
    void handleIoContextChange() override;

  private:
    std::shared_ptr<connection::Serial> serial_con_;
};
} // namespace nodes
