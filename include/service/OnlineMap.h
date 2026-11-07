#pragma once

#include <qinmo/net.h>
#include <unordered_map>
#include <mutex>

namespace my
{

/// @brief record online user with thread-safey
class OnlineMap
{
public:
    void record(int id, const qinmo::net::RTcpConnPtr& ptr);
    void erase(int id);

    int queryId(const qinmo::net::RTcpConnPtr& ptr);

private:
    using MappingTable = std::unordered_map<int, const qinmo::net::RTcpConnPtr&>;
    using ReverseMappingTable = std::unordered_map<qinmo::net::TcpConnection*, int>;

    MappingTable table_;
    ReverseMappingTable rTable_;

    std::mutex mutex_;

};
} // namespace my
