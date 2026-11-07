#include "ChatService.h"
#include "MessageType.h"

namespace my
{

ChatService& ChatService::getInstance()
{
    static ChatService ser;
    return ser;
}

MsgHandler ChatService::getHandler(const json& js)
{
    MessageType msgType = js["msg_type"].get<MessageType>();
    switch (msgType)
    {
        case MessageType::MsgLogin:
        {
            return
                [this](const qinmo::net::RTcpConnPtr& conn, json& js, qinmo::Timestamp timestamp)
                {
                    loginMessage(conn, js, timestamp);
                };
        }

        case MessageType::MsgRegister:
        {
            return
                [this](const qinmo::net::RTcpConnPtr& conn, json& js, qinmo::Timestamp timestamp)
                {
                    registerMessage(conn, js, timestamp);
                };
        }

        default:
        {
            return nullptr;
        }
    }
}



void ChatService::loginMessage(const qinmo::net::RTcpConnPtr& conn, json& js, qinmo::Timestamp timestamp)
{
    int id = js["id"];
    std::string password_hash = js["password_hash"];

    User user = userModel_.query(id);
    QINMO_INFO("ChatService::loginMessage: id:", user.id, " name:", user.name, " password_hash:", user.password_hash);
    if (-1 != user.id)
    {
        // repeat login
        if (1 == user.state)
        {
            json response;
            response["msg_type"] = MessageType::MsgLoginAck;
            response["errno"] = 3;
            conn->send(response.dump());
            return;
        }

        // failed to update
        user.state = 1;
        if (!userModel_.update(user))
        {
            json response;
            response["msg_type"] = MessageType::MsgLoginAck;
            response["errno"] = 4;
            conn->send(response.dump());
            return;
        }

        // login successful
        json response;
        response["msg_type"] = MessageType::MsgLoginAck;
        response["errno"] = 0;
        response["id"] = user.id;
        response["name"] = user.name;
        conn->send(response.dump());
    }
    else
    {
        // query failed
        if (password_hash == user.password_hash)
        {
            // user does not exists
            json response;
            response["msg_type"] = MessageType::MsgLoginAck;
            response["errno"] = 2;
            conn->send(response.dump());
        }
        else
        {
            // password incorrect
            json response;
            response["msg_type"] = MessageType::MsgLoginAck;
            response["errno"] = 1;
            conn->send(response.dump());
        }
    }
}

void ChatService::registerMessage(const qinmo::net::RTcpConnPtr& conn, json& js, qinmo::Timestamp timestamp)
{
    std::string name = js["name"];
    std::string password_hash = js["password_hash"];

    User user;
    user.name = name;
    user.password_hash = password_hash;
    QINMO_INFO("ChatService::registerMessage: ", user.name, " - ", user.password_hash);
    if (userModel_.insert(user))
    {
        json response;
        response["msg_type"] = MessageType::MsgRegisterAck;
        response["errno"] = 0;
        response["id"] = user.id;
        conn->send(response.dump());
    }
    else
    {
        json response;
        response["msg_type"] = MessageType::MsgRegisterAck;
        response["errno"] = 1;
        conn->send(response.dump());
    }
}
} // namespace my
