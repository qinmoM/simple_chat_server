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
    static ChatService& getInstance()
    {
        static ChatService ser;
        return ser;
    }

    MsgHandler getHandler(const json& js)
    {
        QINMO_INFO("json id: ", js["id"].get<int>());
        return nullptr;
    }
private:
    ChatService() { }
};
} // namespace my
