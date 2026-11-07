#include "UserModel.h"
#include "MysqlPool.h"

namespace my
{
bool UserModel::insert(User& user)
{
    std::string sql = "insert into users(name, password_hash, state) values('" + user.name
        + "', '" + user.password_hash + "', " + std::to_string(user.state) + ");";

    auto conn = MysqlPool::getInstance().borrow();
    if (!conn)
    {
        QINMO_ERROR("UserModel::insert: Failed to borrow a Mysql connection.");
        return false;
    }

    if (conn->execute(sql))
    {
        user.id = conn->getInsertId();
        return true;
    }

    QINMO_ERROR("UserModel::insert: Failed to execute sql.");
    return false;
}

User UserModel::query(int id)
{
    std::string sql = "select * from users where id = " + std::to_string(id) + ';';

    auto conn = MysqlPool::getInstance().borrow();
    if (!conn)
    {
        QINMO_ERROR("UserModel::query: Failed to borrow a Mysql connection.");
        return User{ };
    }

    if (!conn->execute(sql))
    {
        QINMO_ERROR("UserModel::query: Failed to execute sql.");
        return User{ };
    }

    User user;
    auto res = conn->getResult();
    if (!res->next())
        return User{ };

    user.id = std::stoi(res->getString().value_or("-1")); // id
    user.name = res->getString().value(); // name
    user.password_hash = res->getString().value(); // password_hash
    user.state = std::stoi(res->getString().value_or("-1")); // state

    if (res->next())
        QINMO_ERROR("UserModel::query: Double id???");

    return user;
}

bool UserModel::update(User& user)
{
    std::string sql = "update users set name = '" + user.name + "', password_hash = '"
        + user.password_hash + "', state = " + std::to_string(user.state)
        + " where id = " + std::to_string(user.id) + ';';

    auto conn = MysqlPool::getInstance().borrow();
    if (!conn)
    {
        QINMO_ERROR("UserModel::update: Failed to borrow a Mysql connection.");
        return false;
    }

    if (conn->execute(sql))
        return true;

    QINMO_ERROR("UserModel::update: Failed to execute sql:", sql);
    return false;
}
} // namespace my
