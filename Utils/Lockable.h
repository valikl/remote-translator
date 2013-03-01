#pragma once

class Lockable
{
public:

    virtual ~Lockable() = 0;

    // true if the locking succeeds, false otherwise.
    // This function hangs until the object is locked.
    // If the locking fails, the state of the object is unknown.
    virtual bool lock() = 0;

    // Lock the object.
    // true is the unlocking succeeds, false otherwise.
    // If the locking fails, the state of the object is unknown.
    virtual bool unlock() = 0;
};

