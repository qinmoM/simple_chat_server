#pragma once

#include "json.hpp"
#include "UserModel.h"
#include <qinmo/net.h>

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
    UserModel userModel_;

};
} // namespace my
