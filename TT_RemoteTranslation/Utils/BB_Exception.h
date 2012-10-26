#ifndef BB_EXCEPTION_H
#define BB_EXCEPTION_H

#pragma once

#include <exception>
#include <string>
#include <sstream>

using std::wstring;
using std::exception;
using std::wostringstream;

/**
 *  Base class for predefined exceptions
 **/
class BB_Exception : public exception
{
public:
    BB_Exception(const wstring& sInfo) :
      m_sInfo(sInfo)
    {
    }

    virtual ~BB_Exception(void) throw()
    {
    }

    virtual wstring ToString() const
    {
        std::wostringstream stream;
        stream<<GetName()<<L": "<<m_sInfo<<L"\n";
        return stream.str();
    }

    virtual const wstring& GetName() const
    {
        static const wstring sName(L"Exception");
        return sName;
    }

    const wstring& GetInfo() const
    {
        return m_sInfo;
    }

protected:
    wstring m_sInfo;
};

#define THROW_SE(exceptionToThrow, problem) \
{\
    wostringstream stream; \
    stream<< problem;\
    throw exceptionToThrow(stream.str());\
}

#endif // BB_EXCEPTION_H
