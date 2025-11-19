#ifndef AST_H

#define AST_H

typedef enum {
  NODE_H1,
  NODE_H2,
  NODE_H3,
  NODE_H4,
  NODE_H5,
  NODE_H6,
  NODE_PARAGRAPH,
  NODE_BLOCKQUOTE,
  NODE_CODEBLOCK_DELIM,
  NODE_CODEBLOCK,
  NODE_LIST_ITEM,
  NODE_LIST_START,
  NODE_LIST_END,
  NODE_EMPTY
} NodeType;

typedef struct ASTNode {
  NodeType type;
  char *text;
  struct ASTNode *next;
} ASTNode;

ASTNode *ast_create(NodeType type, const char *text);
ASTNode *ast_create_int(NodeType type, int value);
void ast_append(ASTNode **head, ASTNode *node);
void ast_print(const ASTNode *head);
void ast_free(ASTNode *head);

#endif
// AST_H
