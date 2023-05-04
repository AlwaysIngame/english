#pragma once

#include "util.h"
#include "sds.h"
#include <string.h>

enum Type {
    OUTFILE,
    INFILE,
    PIPE,
    OUTAPPEND,
    IDENTIFIER,
    NEWLINE,
    ENDFILE,
};


typedef struct Token {

    enum Type type;
    sds text;

} Token;

typedef Token* TokenVec;

#define TOKEN_INIT_NOSTR(t) (Token){.type = t, .text = NULL}

#define TOKEN_INIT(t, s) (Token){.type = t, .text = sdsnew(s)}

#define TOKEN_DELETE(t) sdsfree(t->text)

Token get_keyword(sds text);