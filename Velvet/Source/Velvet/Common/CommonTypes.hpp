#pragma once
#include <cstdint>
#include <limits>

using U8 = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using S8 = int8_t;
using S16 = int16_t;
using S32 = int32_t;
using S64 = int64_t;

using F32 = float;
using F64 = double;

constexpr U8 U8_MAX = std::numeric_limits<U8>::max();
constexpr U16 U16_MAX = std::numeric_limits<U16>::max();
constexpr U32 U32_MAX = std::numeric_limits<U32>::max();
constexpr U64 U64_MAX = std::numeric_limits<U64>::max();

constexpr S8 S8_MAX = std::numeric_limits<S8>::max();
constexpr S16 S16_MAX = std::numeric_limits<S16>::max();
constexpr S32 S32_MAX = std::numeric_limits<S32>::max();
constexpr S64 S64_MAX = std::numeric_limits<S64>::max();

constexpr F32 F32_MAX = std::numeric_limits<F32>::max();
constexpr F64 F64_MAX = std::numeric_limits<F64>::max();
