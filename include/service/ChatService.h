#pragma once

#include "json.hpp"
#include "MessageType.h"
#include "UserModel.h"
#include "OnlineMap.h"

namespace my
{

using nlohmann::json;
using MsgHandler = std::function<void(const qinmo::net::RTcpConnPtr&, json&, qinmo::Timestamp)>;

class ChatService
{
public:
    static ChatService& getInstance();

    MsgHandler getHandler(const json& js);

private:
    ChatService() { }

    void loginMessage(const qinmo::net::RTcpConnPtr& conn, json& js, qinmo::Timestamp timestamp);
    void registerMessage(const qinmo::net::RTcpConnPtr& conn, json& js, qinmo::Timestamp timestamp);

private:
    void sendErrnoMsg(MessageType type, int errnoId, const qinmo::net::RTcpConnPtr& conn);
    bool online(User& user, const qinmo::net::RTcpConnPtr& conn);

private:
    OnlineMap onlineMap_;

    UserModel userModel_;

};
} // namespace my
