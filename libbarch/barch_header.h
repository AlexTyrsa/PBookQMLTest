#pragma once

#include <stdint.h>

#pragma pack(push, 1)

struct barch_header
{
    uint8_t  id[2];
    int32_t width;
    int32_t height;
};

union barch_header_ex
{
    barch_header header;
    uint8_t      raw_data[sizeof(barch_header)];
};

#pragma pack(pop)
