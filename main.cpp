#include "MysqlPool.h"

int main()
{
    my::MysqlPool& pool = my::MysqlPool::getInstance();
    // qinmo::println(1);
    auto conn = pool.borrow();
    // qinmo::println(2);
    conn->execute(R"(select 1;)");
    // qinmo::println(3);
    auto res = conn->getResult();
    // qinmo::println(4);
    while (res->next())
    {
        qinmo::println(res->getString().value());
    }

    // MYSQL* connPtr = mysql_init(nullptr);
    // if (nullptr == connPtr)
    //     qinmo::println("failed to connect.");
    // qinmo::println(connPtr);
    // mysql_query(connPtr, R"(select 1;)");
    return 0;
}