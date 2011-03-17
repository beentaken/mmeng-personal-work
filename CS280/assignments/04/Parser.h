//---------------------------------------------------------------------------
#ifndef PARSERH
#define PARSERH
//---------------------------------------------------------------------------

#include "Common.h"

class Parser
{
  public:
    Parser(const char *InfixExpression);
    ~Parser();
    const ExprNode* Parse(void) throw(ExprTreeException);

  private:
    char *infix_expr_;  // character array passed to constructor
    int curr_pos_;      // position in the array being parsed
    char curr_token_;   // token currently being parsed
    ExprNode* root_;    // tree representation of the expression
    
      // Other private fields and methods
};
#endif
