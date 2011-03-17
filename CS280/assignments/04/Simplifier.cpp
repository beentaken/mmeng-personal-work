/******************************************************************************/
/*!
\file   Simplifier.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #4
\date   2010-03-17
\brief  
  This is an implementation for a class that assists in simplifying a given
  expression tree.

Hours Spent: 4

  Finding memory bugs is the worst part.
*/
/******************************************************************************/

#include "Simplifier.h"
#include <cassert>

/*!\brief A basic constructor for the simplifier helper.
 *
 * \param root
 * 	The root of the expression tree to simplify.
 */
Simplifier::Simplifier(ExprNode* root)
	:root_(root)
{
}

/*!\brief A destructor that does nothing.
 */
Simplifier::~Simplifier()
{
	// Much like the goggles.
}

/*!\brief Starts the simplification process.
 *
 * \return A pointer to the root of the newly simplified tree.
 */
const ExprNode* Simplifier::Simplify(void) throw(ExprTreeException)
{
	SimplifyNode(root_);
	
	return(root_);
}

/*!\brief A helper to deal with root nullity.
 *
 * \param current
 * 	The root node of the tree to handle.
 */
void Simplifier::SimplifyTree(ExprNode* &current)
{
	if (NULL != current)
	{
		SimplifyNode(current);
	}
}

/*!\brief Runs the basic simplification algorithm on the current node.
 *
 * \param current
 * 	The Node to consider for simplification.
 */
void Simplifier::SimplifyNode(ExprNode* &current)
{
	if (NULL == current)
	{
		// This is bad and should never happen.
		throw(ExprTreeException(ExprTreeException::E_BAD_TOKEN, "Did not find expected token."));
	}

	// Well, if this is an identifier or literal, it won't have
	// child nodes.
	if (current->kind == IDENTIFIER || current->kind == LITERAL)
	{
		return; // GTFO!
	}
	// Totally easy. Just simplify one, then the other, amirite?
	SimplifyNode(current->left);
	SimplifyNode(current->right);

	if (NULL == current->left || NULL == current->right)
		return;

	// Now to do things based on individual sets...
	if (current->left->kind == LITERAL && current->right->kind == LITERAL)
	{
		SimplifyTwoLiterals(current);
	}
	else if (current->left->kind == LITERAL && current->right->kind != LITERAL)
	{
		SimplifyLeftLiteral(current);
	}
	else if (current->left->kind != LITERAL && current->right->kind == LITERAL)
	{
		SimplifyRightLiteral(current);
	}
	else if (current->left->kind == IDENTIFIER && current->right->kind == IDENTIFIER)
	{
		SimplifyTwoIDs(current);
	}
}

// We know the rest of these, current must not be NULL, so we won't check.
// Addendun: In release mode, at least.

/*!\brief Deal with a node that has two literal children.
 *
 * \param current
 * 	The Node to deal with.
 */
void Simplifier::SimplifyTwoLiterals(ExprNode* &current)
{
	// Weirdly, assert isn't in the std namespace.
	assert(NULL != current);

	// Only special case: Divide by zero.
	if (DIVIDE_OP == current->data.op && 0 == current->right->data.value)
	{
		// Bad mojo!
		throw(ExprTreeException(ExprTreeException::E_DIVIDE_BY_ZERO, "Whoops, divide by zero."));
	}

	// Now, mess with it.
	switch (current->data.op)
	{
		case PLUS_OP:
			current->data.value = current->left->data.value + current->right->data.value;
			break;
		case MINUS_OP:
			current->data.value = current->left->data.value - current->right->data.value;
			break;
		case MULT_OP:
			current->data.value = current->left->data.value * current->right->data.value;
			break;
		case DIVIDE_OP:
			current->data.value = current->left->data.value / current->right->data.value;
			break;
	}

	current->kind = LITERAL;

	// We have now stuck the results into the current node, let's munch the
	// useless nodes.
	FreeChildren(current);
}

/*!\brief Deal with a Node that has a left-literal childset.
 *
 * \param current
 * 	The Node to deal with.
 */
void Simplifier::SimplifyLeftLiteral(ExprNode* &current)
{
	assert(NULL != current);
	// Check special cases, go!
	
	if (current->left->data.value == 0)
	{
		switch (current->data.op)
		{
			// 0 + E = E
			case PLUS_OP:
				PromoteRightOp(current);
				break;
			// 0 * E = 0
			case MULT_OP: // Fall through, treated the same way.
			// O / E = 0
			case DIVIDE_OP:
				current->data.value = 0;
				current->kind = LITERAL;
				FreeChildren(current);
				break;
			default:
				// Uh, nothing should get here actually.
				break;
		}
	}
	// 1 * E = E
	else if (current->left->data.value == 1 && current->data.op == MULT_OP)
	{
		PromoteRightOp(current);
	}

	// If it wasn't any of the case above, it couldn't be
	// further simplified.
}

/*!\brief Deal with a Node with a right-literal childset.
 *
 * \param current
 * 	The Node to deal with.
 */
void Simplifier::SimplifyRightLiteral(ExprNode* &current)
{
	assert(NULL != current);
	// Social link, go!
	if (0 == current->right->data.value)
	{
		switch (current->data.op)
		{
			// E + 0 = E
			case PLUS_OP: // Fall through...
			// E - 0 = E
			case MINUS_OP:
				PromoteLeftOp(current);
				break;
			// E * 0 = 0
			case MULT_OP:
				current->data.value = 0;
				current->kind = LITERAL;
				FreeChildren(current);
				break;
			// E / 0 = WHAAARBLE
			case DIVIDE_OP:
				throw(ExprTreeException(ExprTreeException::E_DIVIDE_BY_ZERO, "Divvy by 0!"));
				break;	
			default:
				// Why do I even have this section!
				break;
		}
	}
	else if (1 == current->right->data.value)
	{
		switch (current->data.op)
		{
			// E * 1 = E
			case MULT_OP:
			// E / 1 = E
			case DIVIDE_OP:
				PromoteLeftOp(current);
				break;
			default:
				// Oh god the humanity!
				break;
		}
	}
}

/*!\brief Deal with a Node that has two Identification children.
 *
 * \param current
 * 	The Node to deal with.
 */
void Simplifier::SimplifyTwoIDs(ExprNode* &current)
{
	assert(NULL != current);
	assert(NULL != current->left);
	assert(NULL != current->right);

	// Only one case for this.
	if (current->left->data.id == current->right->data.id &&
		(current->data.op == MINUS_OP || current->data.op == DIVIDE_OP))
	{
		switch (current->data.op)
		{
			// I - I = 0
			case MINUS_OP:
				current->data.value = 0;
				break;
			// I / I = 1
			case DIVIDE_OP:
				current->data.value = 1;
				break;
			default:
				// WAAAUUUGH
				break;
		}

		FreeChildren(current);

		current->kind = LITERAL;
	}
}

/*!\brief Replaces the node with its left child.
 *
 * \param current
 * 	The Node to replace.
 */
void Simplifier::PromoteLeftOp(ExprNode* &current)
{
	assert(NULL != current);

	FreeExprTree(current->right);
	ExprNode* temp = current->left;
	*current = *(current->left);
	FreeNode(temp);
}

/*!\brief Replaces the node with its right child.
 *
 * \param current
 * 	The Node to replace.
 */
void Simplifier::PromoteRightOp(ExprNode* &current)
{
	assert(NULL != current);

	FreeExprTree(current->left);
	ExprNode* temp = current->right;
	*current = *(current->right);
	FreeNode(temp);
}

