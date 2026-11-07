#include <OnlineMap.h>

namespace my
{

void OnlineMap::record(int id, const qinmo::net::RTcpConnPtr& ptr)
{
    std::lock_guard<std::mutex> lock(mutex_);
    table_.insert({ id, ptr });
    rTable_.insert({ ptr.get(), id });
}

bool OnlineMap::erase(int id)
{
    std::lock_guard<std::mutex> lock(mutex_);
    return 1 == table_.erase(id);
}

int OnlineMap::queryId(const qinmo::net::RTcpConnPtr& ptr)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = rTable_.find(ptr.get());
    if (it == rTable_.end())
        return -1;

    return it->second;
}
} // namespace my
