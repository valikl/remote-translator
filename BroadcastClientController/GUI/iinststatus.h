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
    INST_ERR_VOL_LEVEL = 6,
    INST_ERR_FIXED_VOL_LEVEL = 101,
    INST_ERR_FIXED_DENOISING = 102,
    INST_ERR_FIXED_ECHO_CANCEL = 103,
    INST_ERR_FIXED_VOICE_ACTIVE = 104,
    INST_ERR_FIXED_AGC = 105,
    INST_ERR_FIXED_VOICE_USER = 106
};

class IInstStatus
{
public:
    virtual void setError(int errcode) = 0;
    virtual void setOK() = 0;
};

#endif // IINSTSTATUS_H
