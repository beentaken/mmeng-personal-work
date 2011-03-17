#include "Common.h"

static int NodeCount = 0;

int GetNodeCount(void)
{
  return NodeCount;
}

void FreeNode(ExprNode* node)
{
  NodeCount--;
  delete node;
}

ExprNode *AllocateNode(void)
{
  NodeCount++;
  return new ExprNode;
}

void FreeExprTree(ExprNode* tree)
{
  if (!tree)
    return;

  FreeExprTree(tree->left);
  FreeExprTree(tree->right);
  FreeNode(tree);
}

void FreeChildren(ExprNode* tree) 
{
  if (!tree)
    return;

  FreeExprTree(tree->left);
  FreeExprTree(tree->right);
  tree->left = 0;
  tree->right = 0;
}

bool IsAddOp(char token)
{
  if ( (token == PLUS_OP) || (token == MINUS_OP) )
    return true;
  else
    return false;
}

bool IsMulOp(char token)
{
  if ( (token == MULT_OP) || (token == DIVIDE_OP) )
    return true;
  else
    return false;
}

bool IsIdentifier(char token)
{
  if ( (token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') )
    return true;
  else
    return false;
}

bool IsLiteral(char token)
{
  if (token >= '0' && token <= '9')
    return true;
  else
    return false;
}
