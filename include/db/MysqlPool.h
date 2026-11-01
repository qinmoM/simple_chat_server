#pragma once

#include "MysqlConn.h"
#include "qinmo/tool/ObjectPool.h"

namespace my
{


class MysqlPool
{
public:
    using PoolType = qinmo::ObjectPool<MysqlConn>;

    static MysqlPool& getInstance()
    {
        static MysqlPool pool;
        return pool;
    }

    PoolType::UniquePtr borrow()
    {
        return pool_->acquire();
    }

private:
    MysqlPool()
    {
        pool_ = PoolType::Builder()
            .setMaxSize(4)
            .setInitSize(4)
            .setMaxIdle(4)
            .setValidateOnAcquire(true)
            .setFuncCreate(
                []()
                {
                    MysqlConn conn;
                    conn.connect("root", "123456", "chat_server");
                    return conn;
                })
            .setFuncValidate(
                [](MysqlConn& conn)
                {
                    return conn.isValid();
                }
            )
            .build();
    }

    std::shared_ptr<qinmo::ObjectPool<MysqlConn>> pool_;
};
} // namespace my
