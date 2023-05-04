#include "lexer.h"

#define WORD_SEGMENT_LEN 16

int peek(FILE *stream) {
    int c = safe_getc(stream);
    if (c != EOF) safe_ungetc(c, stream);
    return c;
}

TokenVec tokenize_line(FILE* stream) {
    TokenVec v = vector_create();
    int c;
    int go = 1;

    while (go) {
        c = safe_getc(stream);
        switch (c) {
            case '>': {
                c = safe_getc(stream);
                if (c == '>') vector_add(&v, TOKEN_INIT_NOSTR(OUTAPPEND));
                else {
                    vector_add(&v, TOKEN_INIT_NOSTR(OUTFILE));
                    safe_ungetc(c,stream);
                }
                break;
            }
            case '<':
                vector_add(&v, TOKEN_INIT_NOSTR(INFILE));
                break;
            case '|':
                vector_add(&v, TOKEN_INIT_NOSTR(PIPE));
                break;
            case '#':
                // Comment case
                while(c != '\n' || c != EOF) c = safe_getc(stream);
                vector_add(&v, TOKEN_INIT_NOSTR(c == '\n' ? NEWLINE : EOF));
                break;
            case ' ':
            case '\r':
            case '\t':
                break;
            case '\n':
                vector_add(&v, TOKEN_INIT_NOSTR(NEWLINE));
                go = 0;
                break;

            case EOF:
                vector_add(&v, TOKEN_INIT_NOSTR(ENDFILE));
                go =0;
                break;
            default:
                safe_ungetc(c, stream);
                vector_add(&v, identifier_token(stream));
                break;
        }
    }
    return v;
}

Token identifier_token(FILE *stream) {
    sds s = sdsempty();
    char go = 1;
    while (go) {
        int c = safe_getc(stream);
        switch (c) {
            case ' ':
            case '\r':
            case '\t':
            case EOF:
                go = 0;
                break;
            case '\n':
                go = 0;
                safe_ungetc('\n', stream);
                break;
            case '\"': {
                sds st = string_read(stream);
                sdscatsds(s, st);
                sdsfree(st);
                break;
            }
            default:
                sdscatlen(s, &c, 1);
                break;
        }
    }
    return get_keyword(s);
}

sds string_read(FILE *stream) {
    sds s = sdsempty();
    while (1) {
        char c = safe_getc(stream);
        if (c == EOF) {
            fprintf(stderr, "Unexpected EOF in string\n");
            abort();
        }
        if (c == '"') return s;

        sdscatlen(s, &c, 1);
    }
}