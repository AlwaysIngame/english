#include "util.h"

void *safe_malloc(size_t n)
{
    void *p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "Fatal: failed to allocate %zu bytes.\n", n);
        abort();
    }
    return p;
}

char *buf_increase_size( char **buf, size_t *restrict n, size_t increase) {

    // Reallocate
    char *tmp = *buf;
    tmp = realloc(tmp, *n + increase);
    if (!tmp) {
        perror("Failed to reallocate buffer");
        return NULL;
    }

    *buf = tmp;
    tmp += *n; // Set to end pos of buffer
    *n += increase;
    return tmp;

}

int safe_getc(FILE *stream) {
    int x = getc(stream);
    if (x == EOF && ferror(stream)) {
        perror("Stream Error");
    }
    return x;
}

int safe_ungetc(int c, FILE * stream) {
    if (c == EOF) return EOF;
    int x = ungetc(c, stream);
    if (x == EOF) {
        perror("Stream Error");
        abort();
    }
    return x;
}