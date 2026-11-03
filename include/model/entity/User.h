#pragma once

#include <string>

namespace my
{

struct User
{
    int id = -1;
    std::string name = "";
    std::string password_hash = "";
    int state = 0;                      // default 0: offline
};
} // namespace my
