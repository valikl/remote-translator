#pragma once

#include <Windows.h>
#include "Lockable.h"

class BB_CriticalSection : public Lockable
{
public:

    /**
    * Constructor.
    */
    BB_CriticalSection();

    /**
    * Destructor.
    */
    virtual ~BB_CriticalSection();

    /**
    * @see Lockable::lock
    */
    virtual bool lock();

    /**
    * @see Lockable::unlock
    */
    virtual bool unlock();

private:
    /// Disallow copy-construction and assignment.
    BB_CriticalSection(const BB_CriticalSection&);
    BB_CriticalSection& operator=(const BB_CriticalSection&);

protected:

    /**
    * The HANDLE of the native critical section object.
    */
    CRITICAL_SECTION m_cs;
};

