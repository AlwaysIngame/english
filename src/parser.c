#include "parser.h"
#include "command.h"
#include "input.h"
#include "sds.h"
#include "token.h"
#include <stdlib.h>

void run_block();

void run_block() {

  new_block();
  Token *t = get_token();

  switch (t->type) {
  case PIPE:
  case INFILE:
  case OUTFILE:
  case OUTAPPEND:
    fprintf(stderr, "Unexpected job control token %d\n", t->type);
    break;
  case NEWLINE:
    run_block();
    break;
  case WORD:
    push_token(t);
    run_command();
    break;
  }
}