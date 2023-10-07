#include "input.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

char *line = NULL;
size_t location = 0;
int eol = 1;

void new_block() {
  location = 0;
  eol = 0;
  line = readline("english> ");
}

void refill() {

  location = 0;
  eol = 0;
  line = readline("> ");
}

int get_char() {

  if (eol)
    refill();

  if (!line)
    return -1;

  if (!line[location])
    eol = 1;

  return line[location] ? line[location] : '\n';
}

void advance() { location++; }