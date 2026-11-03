#pragma once

#include "json.hpp"
#include <qinmo/net.h>

namespace my
{

using nlohmann::json;
using MsgHandler = std::function<void(const qinmo::net::RTcpConnPtr&, qinmo::net::PacketBuffer&, qinmo::Timestamp)>;

class ChatService
{
public:
    static ChatService& getInstance();

    MsgHandler getHandler(const json& js);
private:
    ChatService() { }

    void loginMessage(const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp);
    void registerMessage(const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp);
};
} // namespace my
