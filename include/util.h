#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STREQ(a, b) (!strcmp(a, b))

#define CONDITIONAL_ABORT(condition, error_str)                                \
  if (condition) {                                                             \
    perror(error_str);                                                         \
    abort();                                                                   \
  }

void *safe_malloc(size_t n);

int safe_getc(FILE *stream);

int safe_ungetc(int c, FILE *stream);

char *buf_increase_size(char **buf, size_t *restrict n, size_t increase);