#include "Lock.h"

Lock::Lock(Lockable& lockable): m_lockable(lockable)
{
    m_lockable.lock();
    m_bIsLocked = true;
}

Lock::~Lock()
{
    if (m_bIsLocked)
    {
        m_lockable.unlock();
    }
}

void Lock::Unlock()
{
    if (m_bIsLocked)
    {
        m_bIsLocked = false;
        m_lockable.unlock();
    }
}
