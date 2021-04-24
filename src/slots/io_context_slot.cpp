#include "io_context_slot.hpp"

namespace slots
{

void IoContextSlot::accept(const BaseSlot *slot)
{
    io_ctx_ = static_cast<const IoContextSlot *const>(slot)->value();
    valueChanged();
}

bool IoContextSlot::canConnect(const BaseSlot *const slot) const
{
    return dynamic_cast<const IoContextSlot *const>(slot);
}

std::shared_ptr<boost::asio::io_context> IoContextSlot::value() const
{
    return io_ctx_;
}
} // namespace slots
