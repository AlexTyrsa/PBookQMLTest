#include "include/libbarch.h"

#include "libbarch_chunksize.h"
#include "vector_to_bitmask.h"
#include "barch_header.h"

#include <iterator>
#include <algorithm>

RawImageData::RawImageData(int32_t inWidth, int32_t inHeight, uint8_t *inData) : width(inWidth), height(inHeight)
{
    if(inData && inHeight > 0 && inWidth > 0)
    {
        int32_t dataSize = inHeight * inWidth;

        data.reserve(dataSize + cChunkSize);
        data.assign(inData, inData + dataSize);

        uint8_t fillColor = data.back();

        for(int32_t i = 0; i < cChunkSize; ++i)
            data.push_back(fillColor);

        //storing data + additional extra bytes
    }
    else
        throw std::runtime_error("RawImageData::RawImageData - bad input params");
}

int32_t RawImageData::GetWidth() const
{
    return width;
}

int32_t RawImageData::GetHeight() const
{
    return height;
}

const std::vector<uint8_t> &RawImageData::GetData() const
{
    return data;
}

uint32_t RawImageData::GetDataSize() const
{
    return GetWidth() * GetHeight();
}

BarchCompressor::BarchCompressor(const RawImageData &inData) : width(inData.GetWidth()), height(inData.GetHeight())
{
    DoCompress(inData);
}

std::vector<uint8_t> BarchCompressor::Serialize() const
{
    std::vector<uint8_t> result;

    barch_header_ex header = {{{'B', 'A'}, width, height}};

    std::back_insert_iterator<std::vector<uint8_t>> result_iterator(result);

    std::copy(header.raw_data, header.raw_data + sizeof(barch_header), result_iterator);
    std::copy(index.begin(), index.end(), result_iterator);
    std::copy(data.begin(),  data.end(), result_iterator);

    return result;
}

bool IsRowEmpty(const chunk_type_t* begin, const chunk_type_t* end)
{
    for(const chunk_type_t* i = begin; i != end; ++i)
        if(*i != cEmptyChunk)
            return false;

    return true;
}

void BarchCompressor::DoCompress(const RawImageData &inData)
{
    vector_to_bitmask indexBitmask(index);
    vector_to_bitmask dataBitmask(data);

    for(int32_t row = 0; row < inData.GetHeight(); ++row)
    {
        const chunk_type_t* chunkedData = reinterpret_cast<const chunk_type_t*>(inData.GetData().data() + row * inData.GetWidth());
        int32_t chunkedDataSize = inData.GetWidth() / cChunkSize + (inData.GetWidth() % cChunkSize == 0 ? 0 : 1);

        if(!IsRowEmpty(chunkedData, chunkedData + chunkedDataSize))
        {
            indexBitmask.push0();

            for(int32_t chunkedDataIndex = 0; chunkedDataIndex < chunkedDataSize; ++chunkedDataIndex)
            {
                chunk_type_t chunk = chunkedData[chunkedDataIndex];

                if(chunk == cEmptyChunk)
                {
                    dataBitmask.push0();
                }else if(chunk == cFilledChunk)
                {
                    dataBitmask.push1();
                    dataBitmask.push0();
                }else
                {
                    dataBitmask.push1();
                    dataBitmask.push1();
                    dataBitmask.pushDataChunk(chunk);
                }
            }

            dataBitmask.flush();
        }else
            indexBitmask.push1();
    }

    indexBitmask.flush();
}
