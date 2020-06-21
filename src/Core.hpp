#pragma once

constexpr int EVENT_READ  = 0;
constexpr int EVENT_WRITE = 1;

using OnCallBack = void (*)();

struct event
{
    int fd_;
    int event_type_;
    OnCallBack onCallBack_ = nullptr;
};