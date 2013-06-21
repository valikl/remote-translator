#pragma once
#include <string>

class IWriter
{
public:
    virtual void Write(std::wstring msg)=0;
};

