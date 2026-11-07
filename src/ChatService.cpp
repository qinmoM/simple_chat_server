#include "ChatService.h"

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

    // query failed, user does not exists
    if (-1 == user.id)
        return sendErrnoMsg(MessageType::MsgLoginAck, 2, conn);

    // password incorrect
    if (password_hash != user.password_hash)
        return sendErrnoMsg(MessageType::MsgLoginAck, 1, conn);

    // repeat login
    if (1 == user.state)
        return sendErrnoMsg(MessageType::MsgLoginAck, 3, conn);

    // user online
    if (!online(user, conn))
        return;

    // login successful
    json response;
    response["msg_type"] = MessageType::MsgLoginAck;
    response["errno"] = 0;
    response["id"] = user.id;
    response["name"] = user.name;
    conn->send(response.dump());
}

void ChatService::registerMessage(const qinmo::net::RTcpConnPtr& conn, json& js, qinmo::Timestamp timestamp)
{
    std::string name = js["name"];
    std::string password_hash = js["password_hash"];

    User user;
    user.name = name;
    user.password_hash = password_hash;
    QINMO_INFO("ChatService::registerMessage: ", user.name, " - ", user.password_hash);

    // try to insert user into database
    if (!userModel_.insert(user))
        return sendErrnoMsg(MessageType::MsgRegisterAck, 1, conn);

    json response;
    response["msg_type"] = MessageType::MsgRegisterAck;
    response["errno"] = 0;
    response["id"] = user.id;
    conn->send(response.dump());
}


void ChatService::sendErrnoMsg(MessageType type, int errnoId, const qinmo::net::RTcpConnPtr& conn)
{
    json response;
    response["msg_type"] = type;
    response["errno"] = errnoId;
    conn->send(response.dump());
}

bool ChatService::online(User& user, const qinmo::net::RTcpConnPtr& conn)
{
    // failed to update
    user.state = 1;
    if (!userModel_.update(user))
    {
        json response;
        response["msg_type"] = MessageType::MsgLoginAck;
        response["errno"] = 4;
        conn->send(response.dump());
        return false;
    }

    // record connection
    onlineMap_.record(user.id, conn);
    return true;
}
} // namespace my
