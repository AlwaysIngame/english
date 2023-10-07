#pragma once

#include "sds.h"
#include "util.h"
#include <string.h>

enum Type {
  WORD,
  OUTFILE,
  OUTAPPEND,
  INFILE,
  PIPE,
  NEWLINE,
};

typedef struct Token {

  enum Type type;
  sds text;

} Token;

#define tokenfree(t)                                                           \
  do {                                                                         \
    sdsfree(t->text);                                                          \
    free(t);                                                                   \
  } while (0)

typedef Token *TokenVec;

Token *get_token();
void push_token(Token *);