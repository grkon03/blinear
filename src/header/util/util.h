#pragma once

// macro to enable increments
#define ENABLE_INCR_OPERATORS_ON(T)                               \
    inline T &operator++(T &d, int) { return d = T(int(d) + 1); } \
    inline T &operator++(T &d) { return d = T(int(d) + 1); }      \
    inline T &operator--(T &d, int) { return d = T(int(d) - 1); } \
    inline T &operator--(T &d) { return d = T(int(d) - 1); }

// macro to enable base operators
#define ENABLE_BASE_OPERATORS_ON(T)                              \
    ENABLE_INCR_OPERATORS_ON(T)                                  \
    inline T operator+(T d1, int d2) { return T(int(d1) + d2); } \
    inline T operator-(T d1, int d2) { return T(int(d1) - d2); } \
    inline T operator-(T d) { return T(-int(d)); }               \
    inline T &operator+=(T &d1, int d2) { return d1 = d1 + d2; } \
    inline T &operator-=(T &d1, int d2) { return d1 = d1 - d2; }
