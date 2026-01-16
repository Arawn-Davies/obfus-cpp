#include "io.h"
#include "util.h"
#include <cstdio>

emit_fn acquire_output() {
    static void* f = (void*)&putchar;
    return (emit_fn)f;
}

void emit_char(emit_fn f, int v) {
    f(U8(v));
}
