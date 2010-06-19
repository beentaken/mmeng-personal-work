/* file_header_comment */
#include "map.h"
#include <iostream>

//notice that logging_macros.h uses "long long" type,
//which is not a part of ISO C++, so you need to remove pedantic 
//from the command line - I have 2 targets in make, 
//	gcc0_nopedantic  doesn't have "-pedantic"
//	(use it when FUNCTION_LOG is defined)
//	gcc0 (which I will use for grading) - has "-pedantic"
// see logging_macros.h for details.

//uncomment for debugging (works with GCC and MSC)
//#define FUNCTION_LOG "LOG"
#include "logging_macros.h"

/**************************************************************************
 * Node class starts here.
 */

/* function_header_comment */
CS225::Map::Node::Node(int k,int val,Node* p=NULL,Node* l=NULL,Node* r=NULL) : 
	key(k), value(val), parent(p), left(l), right(r) 
{
	log_it(std::cerr);
}

/* function_header_comment */
int CS225::Map::Node::Key(void) const
{
	log_it(std::cerr);
	return key;
}

/* function_header_comment */
CS225::Map::Node * CS225::Map::Node::first(void)
{
	Node * current = this;
	while (NULL != current && NULL != current->left)
	{
		current = current->left;
	}

	return(current);
}

/* function_header_comment */
CS225::Map::Node * CS225::Map::Node::last(void)
{
	Node * current = this;
	while (NULL != current && NULL != current->right)
	{
		current = current->right;
	}

	return(current);
}

/* function_header_comment */
CS225::Map::Node * CS225::Map::Node::increment(void)
{
	Node * it = this;
	if (!it)
	{
		return it;
	}
	/* Find leftmost child in right subtree
	   This is the successor of it
	   */
	if (it->right)
	{
		Node *p = it->right;
		while (p->left) p = p->left;
		it = p;
	}
	else
	{
		/* Walk up the tree to find the successor of "it"
		   it is the predecessor (rightmost in left subtree)
		   */
		Node *parent = it->parent;
		while (parent && (parent->right == it))
		{
			it = parent;
			parent = it->parent;
		}
		it = parent; /* NULL if at top end() */
	}
	return it;
}

/* function_header_comment */
CS225::Map::Node * CS225::Map::Node::decrement(void)
{
	Node * it = this;
	if (!it)
	{
		return it;
	}

	if (it->left)
	{
		Node * p = it->left;
		while (p->right) p = p->right;
		it = p;
	}
	else
	{
		Node * parent = it->parent;
		while (parent && (parent->left == it))
		{
			it = parent;
			parent = it->parent;
		}
		it = parent;
	}
	return it;

}

/* function_header_comment */
CS225::Map::Node * CS225::Map::Node::find(int key)
{
	Node* curr = this;

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

	return(curr);
}

/**************************************************************************
 * Map_iterator starts here.
 */

/* function_header_comment */
CS225::Map::Map_iterator::Map_iterator(Node *p)
	: p_node(p)
{
	// We be done.
}

/* function_header_comment */
CS225::Map::Map_iterator& CS225::Map::Map_iterator::operator++(void)
{
	if (NULL != p_node)
	{
		p_node = p_node->increment();
	}

	return(*this);
}

/* function_header_comment */
CS225::Map::Map_iterator CS225::Map::Map_iterator::operator++(int)
{
	Map_iterator iter(p_node);

	if (NULL != p_node)
	{
		p_node = p_node->increment();
	}

	return(iter);
}

/* function_header_comment */
int& CS225::Map::Map_iterator::operator*(void)
{
	if (NULL != p_node)
	{
		return(p_node->value);
	}

	return(p_node->value);
}

/* function_header_comment */
const int& CS225::Map::Map_iterator::Key(void) const
{
	return(p_node->key);
}

/* function_header_comment */
bool CS225::Map::Map_iterator::operator!=(const Map_iterator& rhs) const
{
	return(p_node != rhs.p_node);
}

/* function_header_comment */
bool CS225::Map::Map_iterator::operator==(const Map_iterator& rhs) const
{
	return(p_node == rhs.p_node);
}

/**************************************************************************
 * Map_iterator_const starts here.
 */

/* function_header_comment */
CS225::Map::Map_iterator_const::Map_iterator_const(Node *p)
	: p_node(p)
{
	// Insert usefulness here.
}

/* function_header_comment */
CS225::Map::Map_iterator_const& CS225::Map::Map_iterator_const::operator++(void)
{
	if (NULL != p_node)
	{
		p_node = p_node->increment();
	}

	return(*this);
}

/* function_header_comment */
CS225::Map::Map_iterator_const CS225::Map::Map_iterator_const::operator++(int)
{
	Map_iterator_const iter(p_node);

	if (NULL != p_node)
	{
		p_node = p_node->increment();
	}

	return(iter);
}

/* function_header_comment */
const int& CS225::Map::Map_iterator_const::operator*(void)
{
	return(p_node->value);
}

/* function_header_comment */
const int& CS225::Map::Map_iterator_const::Key(void) const
{
	return(p_node->key);
}

/* function_header_comment */
bool CS225::Map::Map_iterator_const::operator!=(const Map_iterator_const& rhs) const
{
	return(p_node != rhs.p_node);
}

/* function_header_comment */
bool CS225::Map::Map_iterator_const::operator==(const Map_iterator_const& rhs) const
{
	return(p_node == rhs.p_node);
}

/**************************************************************************
 * Map class starts here.
 */
CS225::Map::Map_iterator        
		CS225::Map::end_it        = CS225::Map::Map_iterator(NULL);
CS225::Map::Map_iterator_const  
		CS225::Map::const_end_it  = CS225::Map::Map_iterator_const(NULL);

/* function_header_comment */
CS225::Map::Map(void)
	: pRoot(NULL)
{
	// Wisdom like silence.
}

//in implementation file 
//method's name and return value have to be fully qualified with
//all required namespace and class names (like CS225::Map::Map)
//but the argument list does not have to be:
//function argument list automatically falls into the method's namespace

/* function_header_comment */
CS225::Map::Map(const Map& rhs) 
	:pRoot(NULL)
{
	log_it(std::cerr);
	
	my_copy_recursive(&pRoot, rhs.pRoot, NULL);
}

/* returns the depth of the node, used in print_backwards_padded */

/* function_header_comment */
int CS225::Map::getdepth(const Map::Node* node) const
{
	log_it(std::cerr);
	int d = -1;
	while ( node )
	{ 
		++d; 
		node=node->parent;
	}
	return d;
}

/* figure out whether node is left or right child or root 
 * used in print_backwards_padded 
 */

/* function_header_comment */
char CS225::Map::getedgesymbol(const Node* node) const
{
	log_it(std::cerr);
	const Node* parent = node->parent;
	if ( parent == NULL) return '-';
	else                 return ( parent->left == node)?'\\':'/';
}

/* this is another "ASCII-graphical" print, but using 
 * iterative function. 
 * Left branch of the tree is at the bottom
 */

/* function_header_comment */
std::ostream& CS225::operator<<(std::ostream& os, const Map& map)
{
	log_it(std::cerr);
	map.print(os);
	return os;
}

/* function_header_comment */
void CS225::Map::print(std::ostream& os) const
{
#ifdef TENKO_DEBUG
	std::cerr << "print function entered.\n";
#endif
	log_it(std::cerr);
	if (pRoot)
	{
#ifdef TENKO_DEBUG
		std::cerr << "pRoot exists, proceeding to print loop.\n";
#endif
		Map::Node* b = pRoot->last();
		while ( b )
		{ 
#ifdef TENKO_DEBUG
			std::cerr << "Entered print loop.\n";
#endif
			int depth = getdepth(b);
			int i;
			/* printf(b); */

			char edge = getedgesymbol(b);
			switch (edge)
			{
				case '-': 
					for (i=0; i<depth; ++i) std::printf("       ");
					os << b->key << " -> " << b->value << std::endl;
					break;
				case '\\': 
					for (i=0; i<depth; ++i) std::printf("       ");
					os << edge << std::endl;
					for (i=0; i<depth; ++i) std::printf("       ");
					os << b->key << " -> " << b->value << std::endl;
					break;
				case '/': 
					for (i=0; i<depth; ++i) std::printf("       ");
					os << b->key << " -> " << b->value << std::endl;
					for (i=0; i<depth; ++i) std::printf("       ");
					os << edge << std::endl;
					break;
			}
			b = b->decrement();
		}
	}
	std::printf("\n");
}

/* function_header_comment */
void CS225::Map::my_copy_recursive(Node **current, Node *rhs, Node *new_parent)
{
	if (NULL != rhs)
	{
		*current = new Node(rhs->key, rhs->value, new_parent, NULL, NULL);

		my_copy_recursive(&(*current)->left, rhs->left, *current);
		my_copy_recursive(&(*current)->right, rhs->right, *current);
	}
}

/* function_header_comment */
CS225::Map::~Map(void)
{
	delete_nodes(pRoot);
}

/* function_header_comment */
CS225::Map& CS225::Map::operator=(const Map& rhs)
{
	if (this == &rhs)
		return(*this);

	delete_nodes(pRoot);
	pRoot = NULL;

	my_copy_recursive(&pRoot, rhs.pRoot, NULL);

	return(*this);
}

/* function_header_comment */
int& CS225::Map::operator[](int key)
{
	Node * current = (NULL != pRoot) ? NULL : pRoot->find(key);

	if (NULL == current)
	{
#ifdef TENKO_DEBUG
		std::cerr << "current is NULL, insert new value.\n";
#endif
		insert_iterative(&pRoot, key, 0);
		current = pRoot->find(key);
	}
	
#ifdef TENKO_DEBUG
	std::cerr << "current either exists or was insert, value is " << current->value << ".\n";
#endif
	return(current->value);
}

/* function_header_comment */
CS225::Map::Map_iterator CS225::Map::begin(void)
{
	return(Map_iterator(pRoot->first()));
}

/* function_header_comment */
CS225::Map::Map_iterator CS225::Map::end(void)
{
	return(end_it);
//	return(Map_iterator(pRoot->last()));
}

/* function_header_comment */
CS225::Map::Map_iterator CS225::Map::find(int key)
{
	return(Map_iterator(pRoot->find(key)));
}

/* function_header_comment */
void CS225::Map::erase(Map_iterator it)
{
	delete_proper_helper(it.p_node, &pRoot);
}

/* function_header_comment */
CS225::Map::Map_iterator_const CS225::Map::begin(void) const
{
	return(Map_iterator_const(pRoot->first()));
}

/* function_header_comment */
CS225::Map::Map_iterator_const CS225::Map::end(void) const
{
	return(const_end_it);
//	return(Map_iterator_const(pRoot->last()));
}

/* function_header_comment */
CS225::Map::Map_iterator_const CS225::Map::find(int key) const
{
	return(Map_iterator_const(pRoot->find(key)));
}

/* function_header_comment */
void CS225::Map::delete_nodes(Node * current)
{
#ifdef TENKO_DEBUG
	std::cerr << "Entering delete_nodes.\n";
#endif
	if (NULL != current)
	{
		delete_nodes(current->left);
		delete_nodes(current->right);

		delete current;
	}
}

/* function_header_comment */
void CS225::Map::delete_proper_helper(Node * p_delete, Node ** ppRoot)
{
#ifdef TENKO_DEBUG
	std::cerr << "Entering delete_proper_helper.\n";
#endif
	struct Node *parent = p_delete->parent;
	enum Dir {left,right,root} dir;

	/* need to know whether the deleted node is left or right child */
	if ( parent == NULL)
	{
		dir = root;
	}
	else
	{
		dir = (parent->left==p_delete)?left:right;
	}

	/* Has two children. */
	if (NULL != p_delete->left && NULL != p_delete->right)
	{
		Node * successor = (p_delete->increment());

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

	delete(p_delete);
}

/* function_header_comment */
CS225::Map::Node* CS225::Map::insert_iterative(Node ** ppRoot, int key, int value)
{
#ifdef TENKO_DEBUG
	std::cerr << "Entered insert_iterative function with key " << key << " and value " << value << ".\n";
#endif
	Node * current_node = *ppRoot; /* Keep track of where we are. */

	while (true) /* zomg true isn't defined in C89 and needs stdbool.h in C99. */
	{
		if (NULL != current_node)
		{
			if (key > current_node->key)
			{
				if (NULL != current_node->right)
					current_node = current_node->right;
				else
				{
#ifdef TENKO_DEBUG
					std::cerr << "Inserting node at right child.\n";
#endif
					current_node->right = new Node(key, value, current_node, NULL, NULL);
					return(current_node->right);
				}
			}
			else if (key < current_node->key)
			{
				if (NULL != current_node->left)
					current_node = current_node->left;
				else
				{
#ifdef TENKO_DEBUG
					std::cerr << "Inserting node at left child.\n";
#endif
					current_node->left = new Node(key, value, current_node, NULL, NULL);
					return(current_node->left);
				}
			}
			else
			{
				/* We're the same, you and I. */
#ifdef TENKO_DEBUG
				std::cerr << "Node is already in tree? Wut.\n";
#endif
				break;
			}
		}
		else /* This is the first node. */
		{
#ifdef TENKO_DEBUG
			std::cerr << "Inserting node at root.\n";
#endif
			(*ppRoot) = new Node(key, value, NULL, NULL, NULL);
			return(*ppRoot);
			break;
		}
	}

	return(NULL);
}

