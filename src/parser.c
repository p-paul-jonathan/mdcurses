#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "parser.h"

#define MAX_HEADER_LEVEL 6
void parser_state_init(ParserState *st) {
  st->in_code_block = false;
  st->list_level = -1;
}

bool is_code_fence(const char *line) { return strncmp(line, "```", 3) == 0; }

int count_indent(const char *line) {
  int spaces = 0;
  while (line[spaces] == ' ') {
    spaces++;
  }

  return spaces;
}

bool is_in_list(const char *line) {
  int indent_count = count_indent(line);
  const char *trimmed = line + indent_count;

  if (strchr("-+*", trimmed[0]) && trimmed[1] == ' ') {
    return true;
  }

  return false;
}

int calculate_list_level(const char *line) { return count_indent(line) / 2; }

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

  bool list_now = is_in_list(line);

  if (state->list_level >= 0 && !list_now) {
    state->list_level = -1;
    return ast_create(NODE_LIST_END, "");
  }

  if (list_now) {
    int new_level = calculate_list_level(line);

    if (state->list_level == -1) {
      state->list_level = new_level;
      return ast_create_int(NODE_LIST_START, new_level);
    }

    if (new_level == state->list_level) {
      return ast_create(NODE_LIST_ITEM, line);
    }

    if (new_level > state->list_level) {
      state->list_level = new_level;
      return ast_create_int(NODE_LIST_START, new_level);
    }

    if (new_level < state->list_level) {
      int old = state->list_level;
      state->list_level = new_level;
      return ast_create_int(NODE_LIST_END, old);
    }
  }

  if (line[0] == '#') {
    ASTNode *hdr = parse_header(line);
    if (hdr)
      return hdr;
  }

  return ast_create(NODE_PARAGRAPH, line);
}
