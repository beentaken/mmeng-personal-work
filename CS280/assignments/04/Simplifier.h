/******************************************************************************/
/*!
\file   Simplifier.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #4
\date   2010-03-17
\brief  
  This is an header for a class that assists in simplifying a given
  expression tree.
*/
/******************************************************************************/

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
    ExprNode* root_; // current representation of the expression

      // Suggested private methods 
    void SimplifyTree(ExprNode* &current);
    void SimplifyNode(ExprNode* &current);
    void SimplifyTwoLiterals(ExprNode* &current);
    void SimplifyLeftLiteral(ExprNode* &current);
    void SimplifyRightLiteral(ExprNode* &current);
    void SimplifyTwoIDs(ExprNode* &current);
    void PromoteLeftOp(ExprNode* &current);
    void PromoteRightOp(ExprNode* &current);
    
      // Possibly other private fields and methods
};
#endif

