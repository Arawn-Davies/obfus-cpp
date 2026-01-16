#include "core.h"
#include "entropy.h"
#include "io.h"
#include "util.h"

static const int blob[] = {
    72,101,108,108,111,44,32,119,111,114,108,100,33,10
};

void core_run() {
    int noise[16];
    int seed = entropy_seed();

    for (int i = 0; i < 16; ++i)
        noise[i] = rot(seed + MIX(i, seed));

    int key = entropy_fold(noise, 16);

    emit_fn out = acquire_output();

    int decoy = 0;
    for (unsigned i = 0; i < sizeof(blob)/sizeof(blob[0]); ++i) {
        int c = XOR(blob[i], key);
        decoy += rot(c + i);
        emit_char(out, XOR(c, key));
    }

    if (decoy == 0xDEADBEEF)
        emit_char(out, '\0');
}
