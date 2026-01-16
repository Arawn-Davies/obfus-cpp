#ifndef IO_H
#define IO_H

typedef int (*emit_fn)(int);

emit_fn acquire_output();
void emit_char(emit_fn f, int v);

#endif
