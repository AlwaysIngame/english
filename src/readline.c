#include "readline.h"
#include "util.h"

#define SH_GL_BUF_SEGMENT 64

ssize_t sh_getline(char **buf, size_t *restrict bufsize, FILE *restrict stream) {

    if (!*buf || *bufsize == 0) {
        *bufsize = 0;
        if (!buf_increase_size(buf, bufsize, SH_GL_BUF_SEGMENT)) return -1;
    }

    int c;
    char *pos = *buf;
    size_t nread = 0;

    while (1) {
        c = safe_getc(stream);

        *pos = c;
        pos++;
        nread++;

        if (c == '\n') break;
        if (nread + 1 == *bufsize) {
            pos = buf_increase_size(buf, bufsize, SH_GL_BUF_SEGMENT - *bufsize % SH_GL_BUF_SEGMENT);
            if (!*pos) return -1;
        }

    }
    pos[1] = '\0';
    return nread;
}