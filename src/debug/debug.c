#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "debug.h"

//TODO these functions shouldn't repeat the same chunk of code
void error(int n, ...) {
    fprintf(stderr, "An error has occured");

    va_list list;
    va_start(list, n);
    while (n--) {
        fprintf(stderr, " %s", va_arg(list, int));
    }

    va_end(list);
    fprintf(stderr, "\n");
}

void fatal_error(int n, ...) {
    fprintf(stderr, "An fatal error has occured");

    va_list list;
    va_start(list, n);
    while (n--) {
        fprintf(stderr, " %s", va_arg(list, int));
    }

    va_end(list);
    fprintf(stderr, "\n");
    exit(1);
}
