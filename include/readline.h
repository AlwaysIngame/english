#pragma once

#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
Reads a string into the given buffer, allocating memory if necessary.
Buffer must be freed after use.
If either buf is NULL or bufsize is 0, memory will be allocated.
*/
ssize_t sh_getline(char **buf, size_t *restrict bufsize, FILE *restrict stream);
