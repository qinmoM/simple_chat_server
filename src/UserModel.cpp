#include "UserModel.h"
#include "MysqlPool.h"

namespace my
{
bool UserModel::insert(User& user)
{
    std::string sql = "insert into User(name, password_hash, state) values('" + user.name
        + "', '" + user.password_hash + "', '" + std::to_string(user.state) + "');";

    MysqlPool& pool = MysqlPool::getInstance();
    auto conn = pool.borrow();
    if (conn->execute(sql))
    {
        user.id = conn->getInsertId();
        return true;
    }

    return false;
}
} // namespace my
