#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <QMessageBox>

using std::wstring;
using std::exception;
using std::wostringstream;

const int EXCEPTION_ID_DEFAULT(0);
const int EXCEPTION_ID_CONNECTION_LOST(1);

/**
 *  Base class for predefined exceptions
 **/
class BB_Exception : public exception
{
public:
    BB_Exception(const wstring& sInfo, int Id = EXCEPTION_ID_CONNECTION_LOST) :
        m_sInfo(sInfo), m_Id(EXCEPTION_ID_CONNECTION_LOST)
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

    const int GetId() const
    {
        return m_Id;
    }

protected:
    wstring m_sInfo;
    int m_Id;
};

#define THROW_EXCEPT(problem) \
{\
    wostringstream stream; \
    stream<< problem;\
    throw BB_Exception(stream.str());\
}

#define THROW_EXCEPT_WITH_ID(problem, id) \
{\
    wostringstream stream; \
    stream<< problem;\
    throw BB_Exception(stream.str(), id);\
}

#define TRY_FUNC(func) \
try \
{ \
    (func); \
} \
catch(BB_Exception excp) \
{ \
    QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo())); \
}

#define TRY_FUNC_WITH_RETURN(func) \
try \
{ \
    (func); \
} \
catch(BB_Exception excp) \
{ \
    QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo())); \
    return; \
}

#define TRY_BLOCK(block) \
try \
{ \
    block \
} \
catch(BB_Exception excp) \
{ \
    QMessageBox::critical(this, "Error:", QString::fromStdWString(excp.GetInfo())); \
}

#define TRY_BLOCK_RETURN_ON_ERR(block) \
try \
{ \
    block \
} \
catch(BB_Exception excp) \
{ \
    return; \
}

