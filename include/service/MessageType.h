#pragma once

namespace my
{

enum class MessageType : int
{
    MsgLogin = 1,
    MsgLoginAck,
    MsgRegister,
    MsgRegisterAck,
};
} // namespace my
