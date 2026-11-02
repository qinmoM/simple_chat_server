#include "ChatServer.h"

int main()
{
    qinmo::net::EventLoop loop;

    qinmo::net::InetAddr serAddr;
    serAddr.setIP("127.0.0.1");
    serAddr.setPort(7129);

    my::ChatServer server(&loop, serAddr, 4);

    server.start();
    loop.loop();

    return 0;
}