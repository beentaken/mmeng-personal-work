/******************************************************************************/
/*!
\file   Expression.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #4
\date   2010-03-17
\brief  
  This is the implementation for a simple wrapper class around an expression
  tree with a simplifier.
*/
/******************************************************************************/
#include "Expression.h"

/*!\brief Constructor for the Expression tree class.
 *
 * \param InfixExpression
 * 	The equation that the expression tree will represent.
 */
Expression::Expression(const char *InfixExpression)
	:myParser(InfixExpression), root_(NULL)
{
}

/*!\brief A destructor. It does nothing.
 */
Expression::~Expression()
{
}

/*!\brief Tells the internal parser to construct the Expression tree.
 */
void Expression::BuildTree() throw(ExprTreeException)
{
	root_ = const_cast<ExprNode*>(myParser.Parse());
}

/*!\brief Tells the internal simplifier to go through the Expression tree.
 */
void Expression::Simplify() throw(ExprTreeException)
{
	if (NULL == root_)
	{
		BuildTree();
	}

	Simplifier mySimplifier(root_);
	
	root_ = const_cast<ExprNode*>(mySimplifier.Simplify());
}

/*!\brief Retrieves the root node of the expression tree.
 *
 * \return A pointer to the root of the Expression tree.
 */
const ExprNode* Expression::root() const
{
	return(root_);
}

