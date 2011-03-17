/******************************************************************************/
/*!
\file   Parser.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #4
\date   2010-03-17
\brief  
  This is the header for a parser class that turns a specifically-formed
  equation into an expression tree.
*/
/******************************************************************************/
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
		std::string infix_expr_;  // character array passed to constructor
		std::string::const_iterator curr_token_; // Current token being parsed.
		ExprNode* root_;    // tree representation of the expression
    
		// Other private fields and methods
		// Utilities for parsing things.
		void myGetNextToken();

		// Stuff that pseudocode suggests.
		void myMakeExpression(ExprNode* &current);
		void myMakeTerm(ExprNode* &current);
		void myMakeFactor(ExprNode* &current);
};
#endif // PARSERH

