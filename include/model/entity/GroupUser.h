#pragma once

namespace my
{

struct GroupUser
{
    int group_id = -1;
    int user_id = -1;
    int group_role = 0;     // 0: creator, 1: normal
};

} // namespace my
