#include "ChatServer.h"
#include "ChatService.h"

namespace my
{

ChatServer::ChatServer(qinmo::net::EventLoop* loop, const qinmo::net::InetAddr& listenAddr, unsigned int numSubThread)
    : server_(loop, listenAddr, numSubThread)
{
    server_.setMessageFunc(
        [this](const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp)
        {
            message(conn, input, timestamp);
        });

    server_.setConnectFunc(
        [this](const qinmo::net::RTcpConnPtr& conn)
        {
            qinmo::println("connect: ", conn->getfd());
        });

    server_.setDisconnectFunc(
        [this](const qinmo::net::RTcpConnPtr& conn)
        {
            qinmo::println("disconnect: ", conn->getfd());
        });
}

void ChatServer::start()
{
    server_.start();
}



void ChatServer::message(const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp)
{
    std::string msgStr; 
    if (!input.retrieveAll(msgStr))
    {
        QINMO_ERROR("ChatServer::message: Failed to retrieve.");
        return;
    }

    json js = json::parse(msgStr);
    auto handler = ChatService::getInstance().getHandler(js);

    if (!handler)
    {
        QINMO_ERROR("ChatServer::message: Failed to take handler.");
        return;
    }
    handler(conn, input, timestamp);
}
} // namespace my
