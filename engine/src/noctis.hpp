#pragma once

namespace Noctis
{
    typedef unsigned char u8;
    typedef unsigned short u16;
    typedef unsigned int u32;
    typedef unsigned long long u64;

    typedef signed char i8;
    typedef signed short i16;
    typedef signed int i32;
    typedef signed long long i64;

    typedef float f32;
    typedef double f64;

    static_assert(sizeof(u8) == 1, "Expected u8 to be 1 byte");
    static_assert(sizeof(u16) == 2, "Expected u16 to be 2 byte");
    static_assert(sizeof(u32) == 4, "Expected u32 to be 4 byte");
    static_assert(sizeof(u64) == 8, "Expected u64 to be 8 byte");

    static_assert(sizeof(i8) == 1, "Expected i8 to be 1 byte");
    static_assert(sizeof(i16) == 2, "Expected i16 to be 2 byte");
    static_assert(sizeof(i32) == 4, "Expected i32 to be 4 byte");
    static_assert(sizeof(i64) == 8, "Expected i64 to be 8 byte");

    static_assert(sizeof(f32) == 4, "Expected f32 to be 4 bytes");
    static_assert(sizeof(f64) == 8, "Expected f64 to be 8 bytes");
}  // namespace Noctis
