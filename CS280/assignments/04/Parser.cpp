/******************************************************************************/
/*!
\file   Parser.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #4
\date   2010-03-17
\brief  
  This is the implementation for a parser class that can convert a
  specifically-formed equation into an expression tree.
*/
/******************************************************************************/
#include "Parser.h"
#include <string>
#include <cctype>
#include <cstdlib>

namespace
{
	/*********************************************************************
	 * Various useful helpers.
	 */

	/*!\brief Allocates a node, sets things to clean default values.
	 *
	 * \return A nicely allocated node.
	 */
	template<typename T>
	ExprNode* myMakeNode(Kind data_type, const T& data, ExprNode* new_left = NULL, ExprNode* new_right = NULL)
	{
		ExprNode* to_return;

		try
		{
			to_return = AllocateNode();
		}
		catch (std::bad_alloc)
		{
			// Not enough mana.
			throw(ExprTreeException(ExprTreeException::E_NO_MEMORY, "myMakeNode: OOM"));
		}

		if (data_type == OPERATOR)
		{
			to_return->data.op = data;
		}
		else if (data_type == LITERAL)
		{
			to_return->data.value = data - '0'; // Get actual integer value.
		}
		else if (data_type == IDENTIFIER)
		{
			to_return->data.id = data;
		}

		to_return->kind = data_type;

		to_return->left = new_left;
		to_return->right = new_right;

		return(to_return);
	}
}

/*!\brief A constructor for the Parser class.
 *
 * \param InfixExpression
 * 	The equation to parse.
 */
Parser::Parser(const char *InfixExpression)
:infix_expr_(InfixExpression), curr_token_(infix_expr_.begin()), root_(NULL)
{
	// Oh god, what if we have leading spaces?!
	if (std::isspace(*curr_token_))
		myGetNextToken();
}

/*!\brief A destructor for the parser class.
 *
 * Ensures that the tree is properly deallocated.
 */
Parser::~Parser()
{
	FreeExprTree(root_);
}

/*!\brief Tells the Parser to begin checking the equation it was provided.
 *
 * \return A pointer to the root of the newly created expression tree.
 */
const ExprNode* Parser::Parse() throw(ExprTreeException)
{
	myMakeExpression(root_);
	
	return(root_);
}

/*****************************************************************************
 * Private functions.
 */

/*!\brief Moves the internal iterator to the next valid token in the
 * expression provided.
 */
void Parser::myGetNextToken()
{
	if (curr_token_ == infix_expr_.end())
		return;

	do
	{
		++curr_token_;
	} while (curr_token_ != infix_expr_.end() && std::isspace(*curr_token_));

	if (curr_token_ != infix_expr_.end())
	{
		if (!(IsAddOp(*curr_token_) || IsMulOp(*curr_token_) ||
			IsIdentifier(*curr_token_) || IsLiteral(*curr_token_) ||
			*curr_token_ == '(' || *curr_token_ == ')' ))
		{
			throw(ExprTreeException(ExprTreeException::E_BAD_TOKEN, "Bad mojo there."));
		}
	}
}

/*!\brief Begins an Expression segment in the tree.
 *
 * One of three recursive functions that constructs the tree.
 *
 * \param current
 * 	The current node in the tree being worked on.
 */
void Parser::myMakeExpression(ExprNode* &current)
{
	/*
	 * 1  Make a term, setting current to point to it
	 * 2  while the next token is '+' or '-'
	 * 3    Make an operator node, setting left child to current and right to NULL. (current points to new node)
	 * 4    Get the next token.
	 * 5    Make a term, setting the right child of current to point to it.
	 * 6  end while
	*/

	myMakeTerm(current);

	while (curr_token_ != infix_expr_.end() && IsAddOp(*curr_token_))
	{
		ExprNode* temp = myMakeNode(OPERATOR, *curr_token_, current);
		current = temp;

		myGetNextToken();

		myMakeTerm(temp->right);
	}
}

/*!\brief Begins a set of terms in the tree.
 *
 * One of three recursive functions that constructs the tree.
 *
 * \param current
 * 	The current node in the tree being worked on.
 */
void Parser::myMakeTerm(ExprNode* &current)
{
	/*
	 *  7  Make a factor, setting current to point to it
	 *  8  while the next token is '*' or '/'
	 *  9    Make an operator node, setting left child to current and right to NULL(current points to new node)
	 *  10   Get the next token.
	 *  11   Make a factor, setting the right child of current to point to it.
	 *  12 end while
	 */

	myMakeFactor(current);

	while (curr_token_ != infix_expr_.end() && IsMulOp(*curr_token_))
	{
		ExprNode* temp = myMakeNode(OPERATOR, *curr_token_, current);
		current = temp;

		myGetNextToken();

		myMakeFactor(current->right);
	}

}

/*!\brief Constructs a set of factors in the tree.
 *
 * One of three recursive functions that constructs the tree.
 *
 * \param current
 * 	The current node in the tree being worked on.
 */
void Parser::myMakeFactor(ExprNode* &current)
{
	/*
	 * 13  if current token is '(', then
	 * 14    Get the next token
	 * 15    Make an expression, setting current to point to it
	 * 16  else if current token is an IDENTIFIER
	 * 17    Make an identifier node, set current to point to it, set left/right children to NULL. 
	 * 18  else if current token is a LITERAL
	 * 19    Make a literal node, set current to point to it, set left/right children to NULL. 
	 * 20  end if
	 * 21  Get the next token
	 */

	if (curr_token_ == infix_expr_.end())
	{
		return; // Nothing left to parse.
	}

	if (IsAddOp(*curr_token_) || IsMulOp(*curr_token_))
	{
		throw(ExprTreeException(ExprTreeException::E_BAD_TOKEN, "Expected an identifier or literal."));
	}
	else if (*curr_token_ == '(')
	{
		myGetNextToken();

		myMakeExpression(current);
	}
	else if (IsIdentifier(*curr_token_))
	{
		ExprNode* temp = myMakeNode(IDENTIFIER, *curr_token_);
		current = temp;
	}
	else if (IsLiteral(*curr_token_))
	{
		ExprNode* temp = myMakeNode(LITERAL, *curr_token_);
		current = temp;
	}

	myGetNextToken();
}

