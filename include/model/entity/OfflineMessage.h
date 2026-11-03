#pragma once

#include <string>

namespace my
{

struct OfflineMessage
{
    long long id = -1;
    int user_id = -1;
    std::string message = "";
};

} // namespace my
