#pragma once

#include "sds.h"

struct Command;
union FileCommand;

union FileCommand {
  char *name;
  struct Command *cmd;
};

typedef struct Command {
  sds cmd;
  int argc;
  sds *argv;
  union FileCommand pipeTo;
} Command;

void run_command();