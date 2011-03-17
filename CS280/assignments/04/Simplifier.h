//---------------------------------------------------------------------------
#ifndef SIMPLIFIERH
#define SIMPLIFIERH
//---------------------------------------------------------------------------

#include "Common.h"

class Simplifier
{
  public:
    Simplifier(ExprNode* root);
    ~Simplifier();
    const ExprNode* Simplify(void) throw(ExprTreeException);

  private:
    ExprNode* root_; // tree representation of the expression

      // Suggested private methods 
    void SimplifyTree(ExprNode* tree);
    void SimplifyNode(ExprNode* tree);
    void SimplifyTwoLiterals(ExprNode* tree);
    void SimplifyLeftLiteral(ExprNode* tree);
    void SimplifyRightLiteral(ExprNode* tree);
    void SimplifyTwoIDs(ExprNode* tree);
    void PromoteLeftOp(ExprNode* tree);
    void PromoteRightOp(ExprNode* tree);
    
      // Possibly other private fields and methods
};
#endif
