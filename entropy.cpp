#include "entropy.h"
#include "util.h"
#include <cstdlib>

int entropy_seed() {
    std::srand(0xC0FFEE);
    return std::rand();
}

int entropy_fold(const int* p, int n) {
    int v = 0;
    for (int i = 0; i < n; ++i)
        v ^= rot(p[i] + i);
    return U8(v);
}
