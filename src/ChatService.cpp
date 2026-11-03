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
    MessageType msgType = js["id"].get<MessageType>();
    switch (msgType)
    {
        case MessageType::MsgLogin:
        {
            return
                [this](const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp)
                {
                    loginMessage(conn, input, timestamp);
                };
        }

        case MessageType::MsgRegister:
        {
            return
                [this](const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp)
                {
                    registerMessage(conn, input, timestamp);
                };
        }

        default:
        {
            return nullptr;
        }
    }
}

void ChatService::loginMessage(const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp)
{
    ;
}

void ChatService::registerMessage(const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp)
{
    ;
}
} // namespace my
