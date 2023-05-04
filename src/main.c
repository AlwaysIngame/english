#include "lexer.h"
#include "token.h"
#include "vec.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    while (1) {
        TokenVec v = tokenize_line(stdin);

        for (int i = 0; i < vector_size(v); i++) {
            if (v[i].type == ENDFILE) return 0;
            printf("%d\n%s\n----\n", v[i].type, v[i].text);
        }
    }

}