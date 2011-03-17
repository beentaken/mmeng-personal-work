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
    ExprNode* root_;   // tree representation of the expression
};
#endif
