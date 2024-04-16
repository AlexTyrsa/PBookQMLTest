#pragma once

#include "libbarch_chunksize.h"

#include <vector>

class vector_to_bitmask
{
public:
    vector_to_bitmask(std::vector<uint8_t>& inData);

    void push0();
    void push1();
    void pushFlag(bool inValue);
    void pushDataChunk(chunk_type_t inValue);

    void flush();

private:
    void checkIndex();

private:
    std::vector<uint8_t>& data;

    uint8_t chunk;
    int32_t chunkIndex;

};
