#include "CriticalSection.h"

BB_CriticalSection::BB_CriticalSection()
{
    InitializeCriticalSection(&m_cs);
}

BB_CriticalSection::~BB_CriticalSection()
{
    DeleteCriticalSection(&m_cs);
}

bool BB_CriticalSection::lock()
{
    EnterCriticalSection(&m_cs);
    return true;
}

bool BB_CriticalSection::unlock()
{
    LeaveCriticalSection(&m_cs);
    return true;
}
