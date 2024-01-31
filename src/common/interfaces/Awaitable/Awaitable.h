#pragma once
#include <Arduino.h>

class Awaitable
{
public:
    virtual void connect();
    virtual bool isConnected() = 0;
};