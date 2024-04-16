#pragma once

#include <stdint.h>

static const int32_t cChunkSize = 4;

template<int32_t _cChunkSize> struct chunk_type;

template<> struct chunk_type<4>
{
    typedef uint32_t type;
    static const type empty_val = 0xFFFFFFFF;
    static const type filled_val = 0;
};

template<> struct chunk_type<8>
{
    typedef uint64_t type;
    static const type empty_val = 0xFFFFFFFFFFFFFFFF;
    static const type filled_val = 0;
};

typedef chunk_type<cChunkSize>::type chunk_type_t;
static const chunk_type_t cEmptyChunk = chunk_type<cChunkSize>::empty_val;
static const chunk_type_t cFilledChunk = chunk_type<cChunkSize>::filled_val;
