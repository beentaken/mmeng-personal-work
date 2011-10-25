/*!
\file   map.c
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 2
\date   June 5, 2010
\brief
	This file contains implementations for the functions required to
	build a basic BST-based map.

Hours spent on this assignment: 4

Specific portions that gave you the most trouble:

I kept screwing up random pointer stuff.

*/
#include "map.h"
#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */

/* strict C doesn't allow declaration to substitute prototype */
struct Node* create(int key, int value, struct Node* parent,int *perror);

/* definition of Node is hidden from the client (driver)
 * so that client CANNOT use INTERNALS of the Node.
 * this is poor-man encapsulations - hiding implementation details.
 * The main reason for encapsulations -- 
 *   if I ever decide to change Node struct 
 *   no client code will break. Example: I decide to change 
 *   "left" to "Left", all I do is change map.h and map.c, 
 *   no client code is effected, since clients were FORCED 
 *   to use getleft(...) function, rather than field name "left".
 *   Also see typedef in map.h
 */

struct Node
{
	int    key;
	int    value;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
};

/*helper - I use it in insert */
/*!
 * \brief A function to help create new nodes.
 *
 * \param key
 * 	The key to assign to the new node.
 *
 * \param value
 * 	The value to assign to the new node.
 *
 * \param parent
 * 	The parent of the new node.
 *
 * \param perror
 * 	An error code, should anything untowards happen.
 *
 * \return A pointer to the newly created node.
 */
struct Node* create(int key, int value, struct Node* parent,int *perror)
{
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
	if (!new) { *perror=E_NO_MEMORY; return 0; }
	new->key = key;
	new->value = value;
	new->left=0;
	new->right=0;
	new->parent=parent;
	*perror=0;
	return new;
}

/*!
 * \brief Inserts a new node recursively.
 *
 * \param ppRoot
 * 	The root of the tree to work in.
 *
 * \param key
 * 	The key of the new node to insert.
 *
 * \param value
 * 	The value of the new node to insert.
 *
 * \return An error code, or 0 if no error.
 */
int insert_recursive(Node_handle* ppRoot, int key, int value)
{
	int perror = 0;
	if (NULL != *ppRoot)
	{
		/* Left, right, left right, A, B? */
		if (key > getkey(*ppRoot))
		{
			if (NULL != (*ppRoot)->right)
				return insert_recursive(&(*ppRoot)->right, key, value);
			else
			{
				(*ppRoot)->right = create(key, value, *ppRoot, &perror);
			}
		}
		else if (key < getkey(*ppRoot))
		{
			if (NULL != (*ppRoot)->left)
				return insert_recursive(&(*ppRoot)->left, key, value);
			else
			{
				(*ppRoot)->left = create(key, value, *ppRoot, &perror);
			}
		}
		else
		{
			/* We're all the same!
			 * So, what do I do here? Increment the value by the amount?
			 */
		}
	}
	else /* Hmm, we're at an end. Empty tree. Probably should do the real insert here. */
	{
		/* Isn't perror a stdlib function? Huh. */
		*ppRoot = create(key, value, NULL /* This is the root. */, &perror);
	}

	return(perror);
}

/*!
 * \brief Inserts a new node using an interative method.
 *
 * \param ppRoot
 * 	The root of the tree to work in.
 *
 * \param key
 * 	The key of the node to create.
 *
 * \param value
 * 	The value of the node to create.
 *
 * \return An error code, or 0 if no errors.
 */
int insert_iterative(Node_handle* ppRoot, int key, int value)
{
	Node_handle current_node = *ppRoot; /* Keep track of where we are. */
	int perror = 0;

	while (1) /* zomg true isn't defined in C89 and needs stdbool.h in C99. */
	{
		if (NULL != current_node)
		{
			if (key > getkey(current_node))
			{
				if (NULL != current_node->right)
					current_node = current_node->right;
				else
				{
					current_node->right = create( key, value, current_node, &perror);
				}
			}
			else if (key < getkey(current_node))
			{
				if (NULL != current_node->left)
					current_node = current_node->left;
				else
				{
					current_node->left = create(key, value, current_node, &perror);
				}
			}
			else
			{
				/* We're the same, you and I. */
				break;
			}
		}
		else /* This is the first node. */
		{
			(*ppRoot) = create(key, value, NULL, &perror);
			break;
		}
	}

	return(perror);
}

/*!
 * \brief Deletes the node with the given key using a very questionable
 * and slow method.
 *
 * \param ppRoot
 * 	The root of the tree to work in.
 *
 * \param key
 * 	The key of the node to delete.
 */
void delete_silly(Node_handle* ppRoot,int key)
{
	/*reinsert all nodes from the branches into the tree*/
	struct Node *p_delete = *ppRoot;

	/*empty tree case - do nothing*/
	if ( !*ppRoot ) return;

	/*find node to delete*/
	while (p_delete && p_delete->key!=key)
	{
		if (p_delete->key<key) p_delete = p_delete->right;
		else                     p_delete = p_delete->left;
	}

	if (p_delete) {
		struct Node *parent = p_delete->parent;
		struct Node *b;
		if ( !parent )
		{ /*root*/
			*ppRoot=0;
		}
		else
		{ /*cut the subtrees*/
			if (p_delete==parent->left)  parent->left=0;
			if (p_delete==parent->right) parent->right=0;
		}

		/*printf ("deleting node %d\n",p_delete->key);*/
		/*cut the subtrees*/
		/*make subtrees separate trees - otherwise increment won't work properly*/
		if ( p_delete->left)  p_delete->left->parent=0;
		if ( p_delete->right)  p_delete->right->parent=0;


		/*reinsert left subtree*/
		b = first(p_delete->left);
		while ( b )
		{ 
			/*printf ("reinsert from left %d\n",b->key);*/
			insert_recursive(ppRoot,b->key,b->value); 
			b = increment(b);
		}

		/*reinsert left subtree*/
		b = first(p_delete->right);
		while ( b )
		{ 
			/*printf ("reinsert from right %d\n",b->key);*/
			insert_recursive(ppRoot,b->key,b->value); 
			b = increment(b);
		}

		/*clean subtrees*/
		delete_tree(p_delete->left);
		delete_tree(p_delete->right);

		free(p_delete);
	}
}

/*!
 * \brief Gets the key of a given node.
 *
 * \param node
 * 	The node to get the key of.
 *
 * \return The key of the given node.
 */
int getkey(Node_handle const node)
{
	return(node->key);
}

/*!
 * \brief Gets the value of a given node.
 *
 * \param node
 * 	The node to obtain the value of.
 *
 * \return The value of the given node.
 */
int getvalue(Node_handle const node)
{
	return(node->value);
}

/*!
 * \brief Gets the next left node of the given node.
 *
 * \param node
 * 	The node to look to the right of.
 *
 * \return A pointer to the next left node.
 */
Node_handle getleft(Node_handle const node)
{
	return(node->left);
}

/*!
 * \brief Gets the next right node of the given node.
 *
 * \param node
 * 	The node to look to the right of.
 *
 * \return A pointer to the next right node.
 */
Node_handle getright(Node_handle const node)
{
	return(node->right);
}

/*!
 * \brief Sets the value in a given node.
 *
 * \param node
 * 	The node to modify the value of.
 *
 * \param newvalue
 * 	The new value to set.
 */
void setvalue(Node_handle node, int newvalue)
{
	node->value = newvalue;
}

/*!
 * \brief Gets the parent of the given node.
 *
 * \param node
 * 	The node to look at.
 *
 * \return A pointer to the parent of the node. NULL if the node is the root.
 */
Node_handle getparent(Node_handle const node)
{
	return(node->parent);
}

/*!
 * \brief Prints out various debugging information about a node.
 *
 * \param node
 * 	The node to dump info on.
 */
void print(Node_handle node)
{
	printf ("Node: address %p, key %d, value %d, left %p, right %p, parent %p\n",
			(void*)node,
			node->key,
			node->value,
			(void*)node->left,
			(void*)node->right,
			(void*)node->parent
			);
}

/*!
 * \brief Finds a the node to be deleted, then calls delete_proper_helper to
 * 	finish the job.
 *
 * \param ppRoot
 * 	The root of the tree to work in.
 *
 * \param key
 * 	The key of the Node to delete. If the key is not found, nothing happens.
 */
void delete_proper(Node_handle* ppRoot,int key)
{
	struct Node *p_delete = *ppRoot;

	/*empty tree case - do nothing*/
	if ( !*ppRoot ) return;

	/*find node to delete*/
	while (p_delete && p_delete->key!=key)
	{
		if (p_delete->key<key)
		{
			p_delete = p_delete->right;
		}
		else
		{
			p_delete = p_delete->left;
		}
	}

	if (!p_delete) return;
	else delete_proper_helper(p_delete,ppRoot);
}

/*!
 * \brief Assists in deleting a node using the "swap successor" method.
 *
 * \param p_delete
 * 	The node to delete.
 *
 * \param ppRoot
 * 	The root of the tree to work in.
 */
void delete_proper_helper(Node_handle p_delete, Node_handle* ppRoot)
{
	struct Node *parent = getparent(p_delete);
	enum Dir {left,right,root} dir;

	/* need to know whether the deleted node is left or right child */
	if ( parent == NULL)
	{
		dir = root;
	}
	else
	{
		dir = (getleft(parent)==p_delete)?left:right;
	}

	/* Has two children. */
	if (NULL != p_delete->left && NULL != p_delete->right)
	{
		Node_handle successor = increment(p_delete);

		p_delete->key = successor->key;
		p_delete->value = successor->value;

		delete_proper_helper(successor, ppRoot);

		return; /* Make sure we don't short circuit! */
	}
	/* Left child only. */
	else if (NULL != p_delete->left && NULL == p_delete->right)
	{
		switch (dir)
		{
			case left:
				parent->left = p_delete->left;
				parent->left->parent = parent;
				break;
			case right:
				parent->right = p_delete->left;
				parent->right->parent = parent;
				break;
			default:
				/* Root! */
				*ppRoot = p_delete->left;
				(*ppRoot)->parent = NULL;
				break;
		}
	}
	/* Right child only. */
	else if (NULL == p_delete->left && NULL != p_delete->right)
	{
		switch (dir)
		{
			case left:
				parent->left = p_delete->right;
				parent->left->parent = parent;
				break;
			case right:
				parent->right = p_delete->right;
				parent->right->parent = parent;
				break;
			default:
				/* Root! */
				*ppRoot = p_delete->right;
				(*ppRoot)->parent = NULL;
				break;
		}
	}
	/* No children. */
	else
	{
		switch (dir)
		{
			case left:
				parent->left = NULL;
				break;
			case right:
				parent->right = NULL;
				break;
			default:
				/* Root! */
				*ppRoot = NULL;
				break;
		}
	}

	free(p_delete);
}

/*!
 * \brief Deletes a node from the tree.
 *
 * \param ppRoot
 * 	The root of the tree to work in.
 *
 * \param key
 * 	The key of the node to delete.
 */
void delete(Node_handle* ppRoot,int key)
{
	struct Node *p_delete = *ppRoot;

	/*find node to delete*/
	while (p_delete && p_delete->key!=key)
	{
		if (p_delete->key<key) p_delete = p_delete->right;
		else                   p_delete = p_delete->left;
	}

	/* key doesn't exist */
	if (!p_delete)
		return;
	else
	{
		struct Node *parent = getparent(p_delete);
		enum Dir {left,right,root} dir;
		Node_handle to_attach = (p_delete->left) ? p_delete->left : p_delete->right;

		/* need to know whether the deleted node is left or right child */
		if ( parent == NULL)
			dir = root;
		else
			dir = (getleft(parent)==p_delete)?left:right;

		/* If there are any children, set the new parent. */
		if (NULL != to_attach)
		{
			to_attach->parent = parent;
		}

		/* Key exists, let's get to work. */
		switch(dir)
		{
			case left:
				parent->left = to_attach;
				break;
			case right:
				parent->right = to_attach;
				break;
			default:
				/* p_delete is the root? */
				*ppRoot = to_attach;
				break;
		}

		/* If we attached the left, and a right child exists, we'll need
		 * to accomodate that. */
		if ((to_attach == p_delete->left) && (NULL != p_delete->right))
		{
			Node_handle largest = last(to_attach);
			largest->right = p_delete->right;
			p_delete->right->parent = largest;
		}


		/* All done, get rid of p_delete. */
		free(p_delete);
	}
}

/*!
 * \brief Finds a node with a given key in the given subtree.
 *
 * This function works recursively.
 *
 * \param pRoot
 * 	The root node of the subtree to check in.
 *
 * \param key
 * 	The key to look for.
 *
 * \return A pointer to the node containing the key, or NULL if not found.
 */
Node_handle find_recursive(Node_handle const pRoot, int key)
{
	if (!pRoot) return 0;

	if (pRoot->key==key) return pRoot;
	else {
		if (pRoot->key<key) return find_recursive(pRoot->right,key);
		else                  return find_recursive(pRoot->left,key);
	}
}

/*!
 * \brief Finds a node with a given key in the given subtree.
 *
 * This function works iteratively.
 *
 * \param pRoot
 * 	The root node of the subtree to check in.
 *
 * \param key
 * 	The key to look for.
 *
 * \return A pointer to the node containing the key, or NULL if not found.
 */
Node_handle find_iterative(Node_handle const pRoot, int key)
{
	struct Node* curr=pRoot;

	while (curr)
	{
		if (key==curr->key )
			return curr;
		/*printf("at %d\n",curr->key);*/

		if (key<curr->key )
		{
			/*printf("check left\n");*/
			curr=curr->left; 
		}
		else
		{
			/*printf("check right\n");*/
			curr=curr->right;
		}
	}

	return 0;
}

/*!
 * \brief Prints out an entire subtree, starting from the given root node.
 *
 * \param pRoot
 * 	The node to start printing from.
 */
void print_recursive(Node_handle const pRoot)
{
	if (pRoot)
	{
		print_recursive(pRoot->left);
		printf ("%d -> %d;  ",pRoot->key,pRoot->value);
		print_recursive(pRoot->right);
	}
}

/*!
 * \brief Deletes an entire tree starting from the given root node.
 *
 * This function does NOT NULL out the deleted notes, as it is only passed
 * a pointer to the Node and is unable to do so for the root node.
 *
 * Additionally, one can safely assume that the entire subtree is deallocated,
 * and manually setting the root to NULL after calling this function is
 * safe.
 *
 * \param pRoot
 * 	The root node to start free'ing from.
 */
void delete_tree(Node_handle pRoot)
{
	if (NULL != pRoot)
	{
		delete_tree(getleft(pRoot));
		delete_tree(getright(pRoot));

		free(pRoot);
	}
}

/*!
 * \brief Finds the node with the smallest key in the subtree starting from the given root.
 *
 * \param pRoot
 * 	The root node to start looking from.
 *
 * \return A pointer to the smallest node. It will be the root if the root is
 * 	already the smallest.
 */
Node_handle first(Node_handle pRoot)
{
	if (!pRoot) return 0;
	while (pRoot->left) pRoot = pRoot->left;
	return pRoot;
}

/*!
 * \brief Finds the node with the largest key in the subtree starting from the given root.
 *
 * \param pRoot
 * 	The root node to start looking from.
 *
 * \return A pointer to the largest node. It will be the root if the root is
 * 	already the largest.
 */
Node_handle last(Node_handle pRoot)
{
	if (NULL != pRoot)
	{
		while (NULL != getright(pRoot))
			pRoot = getright(pRoot);
	}

	return(pRoot);
}

/*!
 * \brief Locates the node with the smallest key larger than in the provided
 * 	node. Will traverse back up the tree if necessary.
 *
 * \param it
 * 	The node to start checking from.
 *
 * \return The node with the next largest key, NULL if there is nothing else.
 */
Node_handle increment(Node_handle it)
{
	if (!it)
	{
		return it;
	}
	/* Find leftmost child in right subtree
	   This is the successor of it
	   */
	if (it->right)
	{
		struct Node *p = it->right;
		while (p->left) p = p->left;
		it = p;
	}
	else
	{
		/* Walk up the tree to find the successor of "it"
		   it is the predecessor (rightmost in left subtree)
		   */
		struct Node *parent = it->parent;
		while (parent && (parent->right == it))
		{
			it = parent;
			parent = it->parent;
		}
		it = parent; /* NULL if at top end() */
	}
	return it;
}

/*!
 * \brief Locates the node with the largest key smaller than in the provided
 * 	node. Will traverse back up the tree if necessary.
 *
 * \param it
 * 	The node to start checking from.
 *
 * \return The node with the next smallest key, NULL if there is nothing else.
 */
Node_handle decrement(Node_handle it)
{
	if (!it)
	{
		return it;
	}

	if (it->left)
	{
		Node_handle p = it->left;
		while (p->right) p = p->right;
		it = p;
	}
	else
	{
		Node_handle parent = it->parent;
		while (parent && (parent->left == it))
		{
			it = parent;
			parent = it->parent;
		}
		it = parent;
	}
	return it;
}

