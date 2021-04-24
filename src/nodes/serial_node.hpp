#pragma once
#include "../connections/serial_connection.hpp"
#include "../slots/io_context_slot.hpp"
#include "connection_node.hpp"
#include <dt/df/core/span_slot.hpp>
namespace nodes
{
class SerialNode : public ConnectionNode
{
  public:
    static constexpr const char *kKey = "SerialConnectionNode";
    static constexpr const char *kName = "SerialConnection";

  public:
    SerialNode(dt::df::IGraphManager &graph_manager);
    SerialNode(dt::df::IGraphManager &graph_manager, const nlohmann::json &json);
    void calculate() override;
    void processData(std::span<uint8_t> data) override;
    ~SerialNode();

  private:
    void init();

  private:
    std::shared_ptr<connection::Serial> serial_con_;
    std::shared_ptr<dt::df::SpanSlot> rx_data_slot_;
};
} // namespace nodes
