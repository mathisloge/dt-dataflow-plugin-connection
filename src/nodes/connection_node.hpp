#pragma once
#include <dt/df/core/base_node.hpp>
#include "../connections/connection_handle.hpp"
namespace nodes
{
class ConnectionNode : public dt::df::BaseNode, public connection::ConnectionHandle
{
  public:
    using BaseNode::BaseNode;
};
} // namespace nodes
