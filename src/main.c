#include <stdio.h>

#include "ast.h"
#include "parser.h"

#define MAX_LINE_LENGTH 4096

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <markdown-file>\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  FILE *fp = fopen(filename, "r");

  if (!fp) {
    perror("Error opening file");
    return 1;
  }

  char line[MAX_LINE_LENGTH];
  ASTNode *head = NULL;
  ParserState state;

  parser_state_init(&state);

  while (fgets(line, sizeof(line), fp)) {
    ASTNode *node = parse_line(line, &state);
    if (node) {
      ast_append(&head, node);
    }
  }

  fclose(fp);

  ast_print(head);
  ast_free(head);

  return 0;
}
