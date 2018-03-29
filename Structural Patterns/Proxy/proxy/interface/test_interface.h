#pragma once
#include <string>

class ITest {
    virtual std::string GetName() = 0;
    virtual int GetId() = 0;
};