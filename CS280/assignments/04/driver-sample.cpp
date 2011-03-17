#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>

#include "Expression.h"

int tree_height(const ExprNode* tree)
{
  if (tree == 0)
    return -1;

  int lh = tree_height(tree->left);
  int rh = tree_height(tree->right);

  if (lh > rh)
    return lh + 1;
  else
    return rh + 1;
}

//*********************************************************************
// Printing/Debugging
//*********************************************************************
static int Position;
typedef std::map<const ExprNode *, std::pair<int, int> > TNodePositions;
typedef std::pair<const ExprNode *, std::pair<int, int> > TNodePosition;
typedef std::pair<const ExprNode *, int> TNodeLevel;

static TNodePositions NodePositions;

void SetTreePositions(const ExprNode *tree, int depth)
{
  if (!tree)
    return;

  SetTreePositions(tree->left, depth + 1);
  std::pair<int, int>XY(Position++, depth);
  TNodePosition pr(tree, XY);
  NodePositions.insert(pr);
  SetTreePositions(tree->right, depth + 1);
}

void SetTreePositions(const Expression &tree)
{
  Position = 0;
  NodePositions.clear();
  SetTreePositions(tree.root(), 0);
}

std::vector<std::pair<const ExprNode *, int> >GetNodesAtLevel(int level)
{
  std::vector<std::pair<const ExprNode *, int> >nodes;

  TNodePositions::iterator it;
  for (it = NodePositions.begin(); it != NodePositions.end(); ++it)
  {
    std::pair<int, int>XY = it->second;
    if (XY.second == level)
    {
      std::pair<const ExprNode *, int> pr( it->first, XY.first);
      nodes.push_back(pr);
    }
  }
  return nodes;
}  

bool SortNodes(const std::pair<const ExprNode *, int>&a, const std::pair<const ExprNode *, int>&b)
{
  if (a.second < b.second)
    return true;
  else
    return false;
}

void PrintExprTree(const Expression &tree)
{
  SetTreePositions(tree);
  int height = tree_height(tree.root());
  int offset = 0;
  for (int i = 0; i <= height; i++)
  {
    std::vector<TNodeLevel>nodes = GetNodesAtLevel(i);
    std::sort(nodes.begin(), nodes.end(), SortNodes);
    std::vector<TNodeLevel>::iterator iter;
    char buffer[1024] = {0};
    std::memset(buffer, ' ', 1024);
    int fudge = 4;
    for (iter = nodes.begin(); iter != nodes.end(); ++iter)
    {
      char data[10] = {0};
      Kind kind = (*iter).first->kind;
      const char *format;
      if (kind == OPERATOR || kind == IDENTIFIER)
        format = "%c";
      else 
        format = "%i";

      int value = (*iter).first->data.value;
      std::sprintf(data, format, value); 

      offset = (height / 2) + iter->second * fudge;  // fudge factor
      strncpy(buffer + offset, data, strlen(data));
    }
    buffer[offset + fudge] = 0;
    std::cout << buffer << std::endl << std::endl;
  }
}
//*********************************************************************
// End Printing/Debugging
//*********************************************************************

void PrintExpr(const ExprNode* tree)
{
  if (tree == 0)
    return;

  PrintExpr(tree->left);
  switch (tree->kind)
  {
  case OPERATOR:
    std::cout << tree->data.op << " ";
    break;
  case LITERAL:
    std::cout << tree->data.value << " ";
    break;
  case IDENTIFIER:
    std::cout << tree->data.id << " ";
    break;
  default:
    std::cout << "Error in ExprTree" << " ";
    break;
  }
  PrintExpr(tree->right);
}

void PrintFlatTree(const Expression& tree)
{
  PrintExpr(tree.root());
  std::cout << std::endl;
}

typedef void (*DisplayFn)(const Expression& exp);

void SimplifyExpr(const char *expr, DisplayFn print = PrintExprTree)
{
  try 
  {
    std::cout << "****************************************" << std::endl;
    std::cout << "Expression: " << expr << std::endl << std::endl;
    Expression ES(expr);
    ES.BuildTree();
    print(ES);
    ES.Simplify();
    std::cout << "Simplified: " << std::endl;
    print(ES);
    std::cout << std::endl;
  }
  catch (ExprTreeException &e)
  {
    const char *str;
    if (e.code() == ExprTreeException::E_BAD_TOKEN)
      str = "E_BAD_TOKEN";
    else if (e.code() == ExprTreeException::E_DIVIDE_BY_ZERO)
      str = "E_DIVIDE_BY_ZERO";
    else if (e.code() == ExprTreeException::E_NO_MEMORY)
      str = "E_NO_MEMORY";
    else
      str = "Unknown";
    
    std::cout << "***** Exception: (" << str << ") " << e.what() << std::endl << std::endl;
  }
  catch (...) {
    std::cout << "***** Exception with: " << expr << std::endl << std::endl;
  }
}

int main(void)
{
    // What does your compiler do?
  //int a = (6 * 2 - 3) / (3 * 2 - 6);;
  //int b = 5;
  //int c = (b * 2 - 3) / (3 * 2 - 6);

  DisplayFn fn; // = PrintExprTree;
  //fn = PrintFlatTree;

  SimplifyExpr("5 * 9", fn);
  SimplifyExpr("5*9+8 * 4 *6    + 7", fn);
  SimplifyExpr("5 * (((9 + 8) * (4 * 6)) + 7)", fn);
  SimplifyExpr("A * B - 0 + 3 * (C - (C + (3 - 3)))", fn);
  SimplifyExpr("A * B * 0", fn);
  SimplifyExpr("A / A", fn);
  SimplifyExpr("A - A", fn);
  SimplifyExpr("(A + 7) / (A + 7)", fn);
  SimplifyExpr("A / (4 - 1 - 3)", fn);
  SimplifyExpr("A / +", fn);
  SimplifyExpr("A + B * C * (D - E * (F + G - H) / J) + K", fn);
  SimplifyExpr("B / 0", fn);
  SimplifyExpr("0 / 0", fn);
  SimplifyExpr("4 + $", fn);

  std::cout << "Number of nodes allocated but not freed: " << GetNodeCount() << std::endl;

  return 0;
}
