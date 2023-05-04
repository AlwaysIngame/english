#include "token.h"
#include "util.h"

Token get_keyword(sds text) {
    if (STREQ(text, "into")) return TOKEN_INIT_NOSTR(PIPE);
    if (STREQ(text, "to")) return TOKEN_INIT_NOSTR(OUTFILE);
    if (STREQ(text, "appendto")) return TOKEN_INIT_NOSTR(OUTAPPEND);
    if (STREQ(text, "from")) return TOKEN_INIT_NOSTR(INFILE);

    return TOKEN_INIT(IDENTIFIER, text);
}