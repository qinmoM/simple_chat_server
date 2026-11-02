#pragma once

#include <qinmo/net.h>

namespace my
{

class ChatServer
{
public:
    ChatServer(qinmo::net::EventLoop* loop, const qinmo::net::InetAddr& listenAddr, unsigned int numSubThread);

    void start();

private:
    void message(const qinmo::net::RTcpConnPtr& conn, qinmo::net::PacketBuffer& input, qinmo::Timestamp timestamp);

private:
    qinmo::net::TcpServer server_;
};
} // namespace my
