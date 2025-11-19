#ifndef PARSER_H

#define PARSER_H

#include <stdbool.h>

#include "ast.h"

typedef struct {
  bool in_code_block;
} ParserState;

void parser_state_init(ParserState *state);
ASTNode *parse_line(const char *line, ParserState *state);

#endif
// PARSER_H
