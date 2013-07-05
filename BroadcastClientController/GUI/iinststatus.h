#ifndef IINSTSTATUS_H
#define IINSTSTATUS_H

class IInstStatus
{
public:
    virtual void setError() = 0;
    virtual void setOK() = 0;
};

#endif // IINSTSTATUS_H
