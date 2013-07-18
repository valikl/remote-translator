#ifndef IINSTSTATUS_H
#define IINSTSTATUS_H

enum InstErrCode
{
    INST_ERR_NONE = 0,
    INST_ERR_DENOISING = 1,
    INST_ERR_ECHO_CANCEL = 2,
    INST_ERR_VOICE_ACTIVE = 3,
    INST_ERR_AGC = 4,
    INST_ERR_VOICE_USER = 5,
    INST_ERR_VOL_LEVEL = 6
};

class IInstStatus
{
public:
    virtual void setError(int errcode) = 0;
    virtual void setOK() = 0;
};

#endif // IINSTSTATUS_H
