#pragma once

#include "Lockable.h"

class Lock
{
public:

    Lock(Lockable& lockable);
    virtual ~Lock();

    // Unlock the lock
    void Unlock();

private:
    /// Disallow copy-construction and assignment.
    Lock(const Lock&);
    Lock& operator=(const Lock&);

protected:

    // The wrapped Lockable.
    Lockable& m_lockable;

    // Lock state
    bool m_bIsLocked;
};

