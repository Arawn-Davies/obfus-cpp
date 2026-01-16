#ifndef UTIL_H
#define UTIL_H

#define U8(x) ((x) & 0xFF)
#define XOR(a,b) ((a) ^ (b))
#define SHR(a,b) ((a) >> (b))
#define SHL(a,b) ((a) << (b))
#define MIX(a,b) (XOR(SHL(a,1), SHR(b,1)))

static inline int rot(int v) {
    v ^= v << 5;
    v ^= v >> 7;
    v ^= v << 3;
    return v;
}

#endif
