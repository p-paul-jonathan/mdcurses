#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "parser.h"

#define MAX_HEADER_LEVEL 6
void parser_state_init(ParserState *st) {
    st->in_code_block = false;
}

bool is_code_fence(const char *line) { return strncmp(line, "```", 3) == 0; }

ASTNode *parse_header(const char *line) {
  int level = 0;

  while (line[level] == '#') {
    level++;
  }

  if (level == 0 || level > MAX_HEADER_LEVEL) {
    return NULL;
  }
  if (line[level] != ' ') {
    return NULL;
  }

  const char *text = line + level + 1;
  NodeType type = NODE_H1 + (level - 1);

  return ast_create(type, text);
}

ASTNode *parse_line(const char *line, ParserState *state) {
  if (is_code_fence(line)) {
    state->in_code_block = !state->in_code_block;
    return ast_create(NODE_CODEBLOCK_DELIM, line);
  }

  if (state->in_code_block) {
    return ast_create(NODE_CODEBLOCK, line);
  }

  if (line[0] == '#') {
    return parse_header(line);
  }

  return ast_create(NODE_PARAGRAPH, line);
}

