#include "udp_options_node.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>
namespace nodes
{
UdpOptionsNode::UdpOptionsNode(dt::df::core::IGraphManager &graph_manager)
    : SimpleOutputNode<connection::UdpOptions>(graph_manager, std::string{kKey}, std::string{kName})
{}
void UdpOptionsNode::init(dt::df::core::IGraphManager &graph_manager)
{
    output_slot_ = registerOutput(graph_manager, "ConUdpOptions", "options", 0);
}

void UdpOptionsNode::renderCustomContent()
{
    constexpr float kMaxItemWidth = 125.f;
    constexpr std::array<const char *, 3> kStrItems = {"none", "ipv4", "ipv6"};
    const int sel_list_prot = static_cast<int>(value_.listen_protocol);

    ImGui::TextUnformatted("Listen protocol");
    ImGui::SetNextItemWidth(kMaxItemWidth);
    if (ImGui::BeginCombo("##listenproto", sel_list_prot < kStrItems.size() ? kStrItems[sel_list_prot] : "---"))
    {
        for (int n = 0; n < kStrItems.size(); n++)
        {
            const bool is_selected = (sel_list_prot == n);
            if (ImGui::Selectable(kStrItems[n], is_selected))
                value_.listen_protocol = connection::UdpOptions::Protocol{n};
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::TextUnformatted("Listen port");
    ImGui::SetNextItemWidth(kMaxItemWidth);
    ImGui::InputScalar("##listenport", ImGuiDataType_U16, &value_.listen_port);

    ImGui::TextUnformatted("Send Address");
    ImGui::SetNextItemWidth(kMaxItemWidth);
    ImGui::InputText("##sendaddr", &value_.write_address);

    ImGui::TextUnformatted("Send port");
    ImGui::SetNextItemWidth(kMaxItemWidth);
    ImGui::InputScalar("##sendport", ImGuiDataType_U16, &value_.write_port);
}

} // namespace nodes
