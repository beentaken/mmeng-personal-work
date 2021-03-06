/******************************************************************************/
/*!
\file   Expression.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #4
\date   2010-03-17
\brief  
  This is the header for a wrapper class around an expression tree with a
  simplifier.
*/
/******************************************************************************/
//---------------------------------------------------------------------------
#ifndef EXPRESSIONH
#define EXPRESSIONH
//---------------------------------------------------------------------------

#include "Parser.h"
#include "Simplifier.h"

class Expression
{
  public:
    Expression(const char *InfixExpression);
    ~Expression();

      // Create expression tree from input
    void BuildTree(void) throw(ExprTreeException);

      // Simplify the expression tree by folding constants, etc.
    void Simplify(void) throw(ExprTreeException);

      // For debugging and external access
    const ExprNode* root(void) const;
    
  private:
    Parser myParser;
    ExprNode* root_;   // tree representation of the expression
};
#endif

