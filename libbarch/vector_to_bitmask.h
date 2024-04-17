#pragma once

#include "libbarch_chunksize.h"

#include <vector>

class o_vector_to_bitmask
{
public:
    o_vector_to_bitmask(std::vector<uint8_t>& inData);

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

class i_vector_to_bitmask
{
public:
    i_vector_to_bitmask(const std::vector<uint8_t>& inData);

    bool pop();
    chunk_type_t popDataChunk();

    bool isPopPossible() const;

    void drop();

private:
    void checkIndex();

private:
    const std::vector<uint8_t>& data;

    int32_t chunkIndex;
    int32_t dataIndex;

};
