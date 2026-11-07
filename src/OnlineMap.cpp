#include <OnlineMap.h>

namespace my
{

void OnlineMap::record(int id, const qinmo::net::RTcpConnPtr& ptr)
{
    std::lock_guard<std::mutex> lock(mutex_);
    table_.insert({ id, ptr });
}
} // namespace my
