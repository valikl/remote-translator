#pragma once
#include <string>

// Usage
// VideoJob *obj = new VideoJob();
// Thread thread = new Thread(obj);

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";

class BB_Base64
{
public:

    BB_Base64();
    ~BB_Base64();

    static std::string base64Decode(std::string const& encoded_string);

private:
    static bool isBase64(unsigned char c);

};





