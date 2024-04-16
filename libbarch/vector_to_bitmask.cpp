#include "vector_to_bitmask.h"

vector_to_bitmask::vector_to_bitmask(std::vector<uint8_t> &inData) : data(inData), chunk(0), chunkIndex(0)
{

}

void vector_to_bitmask::push0()
{
    ++chunkIndex;
    checkIndex();
}

void vector_to_bitmask::push1()
{
    chunk |= 1 << chunkIndex;
    ++chunkIndex;
    checkIndex();
}

void vector_to_bitmask::pushFlag(bool inValue)
{
    if(inValue)
        push1();
    else
        push0();
}

void vector_to_bitmask::pushDataChunk(chunk_type_t inValue)
{
    for(int32_t i = 0; i < cChunkSize * 8; ++i)     //can be optimized
    {
        pushFlag(inValue & 1);

        inValue >>= 1;
    }
}

void vector_to_bitmask::flush()
{
    if(chunkIndex != 0)
    {
        data.push_back(chunk);
        chunk = 0;
        chunkIndex = 0;
    }
}

void vector_to_bitmask::checkIndex()
{
    if(chunkIndex >= 7)
    {
        data.push_back(chunk);
        chunk = 0;
        chunkIndex = 0;
    }
}
