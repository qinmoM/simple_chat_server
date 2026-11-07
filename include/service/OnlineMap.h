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
    using MappingTable = std::unordered_map<int, const qinmo::net::RTcpConnPtr&>;

    void record(int id, const qinmo::net::RTcpConnPtr& ptr);
    void erase();

private:
    MappingTable table_;

    std::mutex mutex_;

};
} // namespace my
