#include "vector_to_bitmask.h"

o_vector_to_bitmask::o_vector_to_bitmask(std::vector<uint8_t> &inData) : data(inData), chunk(0), chunkIndex(0)
{

}

void o_vector_to_bitmask::push0()
{
    checkIndex();
}

void o_vector_to_bitmask::push1()
{
    chunk |= 1 << chunkIndex;
    checkIndex();
}

void o_vector_to_bitmask::pushFlag(bool inValue)
{
    if(inValue)
        push1();
    else
        push0();
}

void o_vector_to_bitmask::pushDataChunk(chunk_type_t inValue)
{
    for(int32_t i = 0; i < cChunkSize * 8; ++i)     //can be optimized
    {
        pushFlag(inValue & 1);

        inValue >>= 1;
    }
}

void o_vector_to_bitmask::flush()
{
    if(chunkIndex != 0)
    {
        data.push_back(chunk);
        chunk = 0;
        chunkIndex = 0;
    }
}

void o_vector_to_bitmask::checkIndex()
{
    ++chunkIndex;

    if(chunkIndex > 7)
    {
        data.push_back(chunk);
        chunk = 0;
        chunkIndex = 0;
    }
}

i_vector_to_bitmask::i_vector_to_bitmask(const std::vector<uint8_t> &inData) : data(inData), chunkIndex(0), dataIndex(0)
{

}

bool i_vector_to_bitmask::pop()
{
    if(!isPopPossible())
        throw std::runtime_error("i_vector_to_bitmask::pop not enouth data");

    bool result = (data[dataIndex] & (1 << chunkIndex)) != 0;

    checkIndex();

    return result;
}

chunk_type_t i_vector_to_bitmask::popDataChunk()
{
    chunk_type_t result = 0;

    for(int32_t i = 0; i < cChunkSize * 8; ++i)     //can be optimized
    {
        result >>= 1;

        bool val = pop();

        if(val)
            result |= 0x80000000;
    }

    return result;
}

bool i_vector_to_bitmask::isPopPossible() const
{
    return dataIndex < data.size();
}

void i_vector_to_bitmask::drop()
{
    if(chunkIndex != 0)
    {
        chunkIndex = 0;
        ++dataIndex;
    }
}

void i_vector_to_bitmask::checkIndex()
{
    ++chunkIndex;

    if(chunkIndex > 7)
    {
        chunkIndex = 0;
        ++dataIndex;
    }
}
