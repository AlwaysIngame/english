#pragma once

#include <stdlib.h>
#include <unistd.h>
#include "token.h"
#include "sds.h"
#include "vec.h"

typedef struct CommandList {

    sds program;
    sds *args;
    struct CommandList *next;

} CommandList;

#define NEW_CMD (Command) {.program = sdsnew(), .args = vector_create()}

#define DEL_CMD(c) sdsfree(c.program); for (int i = 0; i < vector_size(c); i++) sdsfree(c.args[i]); vector_free(c.args)

#define insert_arg(cmd, arg) vector_add(&cmd.args, arg)

typedef struct Outfile {

    int fd;
    sds file;

} Outfile;

typedef struct Pipeline {

    CommandList *commands;
    sds infile;
    Outfile *outfiles;

} Pipeline;