#pragma once

#include <stdint.h>
#include <vector>

class RawImageData
{
public:
    RawImageData(int32_t inWidth, int32_t inHeight, uint8_t* inData);

    int32_t GetWidth() const;
    int32_t GetHeight() const;

    const std::vector<uint8_t>& GetData() const;
    uint32_t GetDataSize() const;

    RawImageData() = delete;
    RawImageData(const RawImageData&) = delete;
    RawImageData& operator =(const RawImageData&) = delete;

private:
    int32_t                width;            // image width in pixels
    int32_t                height;           // image height in pixels
    std::vector<uint8_t>   data;             // image data. data[j * width + i] is color of pixel in row j and column i.

};

class BarchCompressor
{
public:
    BarchCompressor(const RawImageData& inData);

    std::vector<uint8_t> Serialize() const;

    BarchCompressor() = delete;
    BarchCompressor(const BarchCompressor&) = delete;
    BarchCompressor& operator =(const BarchCompressor&) = delete;

private:
    void DoCompress(const RawImageData& inData);

private:
    int32_t               width;            // image width in pixels
    int32_t               height;           // image height in pixels
    std::vector<uint8_t>  index;            // pointer to index table. size = height / 8 + (height % 8 == 0 ? 0 : 1) for each bit 1 mean empty row, 0 mean non empty row
    std::vector<uint8_t>  data;             // compressed data

};
