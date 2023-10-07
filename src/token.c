#include "token.h"
#include "input.h"
#include "sds.h"
#include <string.h>

struct TokenStack {
  Token *tok;
  struct TokenStack *next;
};

struct TokenStack *tokenStack = NULL;

enum STATE {
  T_START,	// Only whitespace has been read so far
  T_RIGHTCARET, // A > has just been read
  T_WORD,	// A non identifiable string is being read in

};

Token *parse_token() {

  Token *t = malloc(sizeof(Token));
  t->type = WORD;
  t->text = NULL;

  int c;
  enum STATE state = T_START;

  while (1) {
    c = get_char();
    if (state == T_START) {
      advance();
      if (c == ' ' || c == '\t')
	advance();
      else if (c == '|') {
	t->type = PIPE;
	return t;
      } else if (c == '>') {
	state = T_RIGHTCARET;
      } else if (c == '\n') {
	t->type = NEWLINE;
	return t;
      } else {
	t->text = sdsempty();
	t->text = sdscatlen(t->text, &c, 1);
	state = T_WORD;
      }
    } else if (state == T_RIGHTCARET) {
      if (c == '>') {
	t->type = OUTAPPEND;
	advance();
	return t;
      } else {
	t->type = OUTFILE;
	return t;
      }
    } else if (state == T_WORD) {
      if (c == ' ' || c == '\n') {
	return t;
      }
      t->text = sdscatlen(t->text, &c, 1);
      advance();
    }
  }
}

Token *get_token() {
  if (tokenStack) {
    struct TokenStack t = *tokenStack;
    free(tokenStack);
    tokenStack = t.next;
    return t.tok;
  }
  return parse_token();
}

void push_token(Token *t) {
  struct TokenStack *stack = malloc(sizeof(struct TokenStack));
  stack->next = tokenStack;
  stack->tok = t;
  tokenStack = stack;
}
