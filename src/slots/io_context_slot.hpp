#pragma once
#include <memory>
#include <boost/asio.hpp>
#include <dt/df/core/base_slot.hpp>
namespace slots
{
class IoContextSlot final : public dt::df::BaseSlot
{
  public:
    using BaseSlot::BaseSlot;

    void accept(const BaseSlot *slot) override;
    bool canConnect(const BaseSlot *const slot) const override;
    std::shared_ptr<boost::asio::io_context> value() const;

  private:
    std::shared_ptr<boost::asio::io_context> io_ctx_;
};
} // namespace slots
