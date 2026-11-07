#pragma once

#include "User.h"

namespace my
{

class UserModel
{
public:
    bool insert(User& user);
    User query(int id);
};
} // namespace my
