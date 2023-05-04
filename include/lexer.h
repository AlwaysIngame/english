#pragma once

#include "token.h"
#include "util.h"
#include "sds.h"
#include "vec.h"
#include <stdlib.h>

sds string_read(FILE *stream);

Token identifier_token(FILE *stream);

TokenVec tokenize_line(FILE* stream);