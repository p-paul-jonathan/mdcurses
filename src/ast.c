#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

ASTNode *ast_create(NodeType type, const char *text) {
  ASTNode *node = malloc(sizeof(ASTNode));

  node->type = type;
  node->text = text ? strdup(text) : NULL;
  node->next = NULL;

  return node;
}

void ast_append(ASTNode **head, ASTNode *node) {
  if (*head == NULL) {
    *head = node;
    return;
  }

  ASTNode *curr = *head;

  while (curr->next != NULL) {
    curr = curr->next;
  }

  curr->next = node;
}

void ast_print(const ASTNode *head) {
  while (head) {
    switch (head->type) {
    case NODE_H1:
      printf("NODE_H1 %s\n", head->text);
      break;
    case NODE_H2:
      printf("NODE_H2 %s\n", head->text);
      break;
    case NODE_H3:
      printf("NODE_H3 %s\n", head->text);
      break;
    case NODE_H4:
      printf("NODE_H3 %s\n", head->text);
      break;
    case NODE_H5:
      printf("NODE_H3 %s\n", head->text);
      break;
    case NODE_H6:
      printf("NODE_H3 %s\n", head->text);
      break;
    case NODE_PARAGRAPH:
      printf("PARAGRAPH %s\n", head->text);
      break;
    case NODE_BLOCKQUOTE:
      printf("BLOCKQUOTE %s\n", head->text);
      break;
    case NODE_CODEBLOCK_DELIM:
      printf("CODEBLOCK_DELIM\n");
      break;
    case NODE_CODEBLOCK:
      printf("CODEBLOCK %s\n", head->text);
      break;
    case NODE_EMPTY:
      printf("EMPTY\n");
      break;
    }
    head = head->next;
  }
}

void ast_free(ASTNode *head) {
  while (head) {
    ASTNode *next = head->next;
    if (head->text)
      free(head->text);
    free(head);
    head = next;
  }
}
