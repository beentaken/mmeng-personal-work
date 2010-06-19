#include "map.h"
#include <stdlib.h>
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

struct Node {
  int    key;
  int    value;
  struct Node *left;
  struct Node *right;
  struct Node *parent;
};


/*helper - I use it in insert */
struct Node* create(int key, int value, struct Node* parent,int *perror) {
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

int insert_recursive(Node_handle* ppRoot, int key, int value) {
}

int  insert_iterative(Node_handle* ppRoot, int key, int value) {
}

void delete_silly(Node_handle* ppRoot,int key) {
	/*reinsert all nodes from the branches into the tree*/
	struct Node *p_delete = *ppRoot;

	/*empty tree case - do nothing*/
	if ( !*ppRoot ) return;

	/*find node to delete*/
	while (p_delete && p_delete->key!=key) {
		if (p_delete->key<key) p_delete = p_delete->right;
		else                     p_delete = p_delete->left;
	}

	if (p_delete) {
		struct Node *parent = p_delete->parent;
		struct Node *b;
		if ( !parent ) { /*root*/
			*ppRoot=0;
		} else { /*cut the subtrees*/
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
		while ( b ) { 
			/*printf ("reinsert from left %d\n",b->key);*/
			insert_recursive(ppRoot,b->key,b->value); 
			b = increment(b);
		}

		/*reinsert left subtree*/
		b = first(p_delete->right);
		while ( b ) { 
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

int getkey(Node_handle const node) {
}

int getvalue(Node_handle const node) {
}

Node_handle getleft(Node_handle const node) {
}

Node_handle getright(Node_handle const node) {
}

void setvalue(Node_handle node, int newvalue) {
}

Node_handle getparent(Node_handle node) {
}

/* may be useful for debugging */
void print(Node_handle node) {
	printf ("Node: address %p, key %d, value %d, left %p, right %p, parent %p\n",
			(void*)node,
			node->key,
			node->value,
			(void*)node->left,
			(void*)node->right,
			(void*)node->parent
			);
}

/* this function just finds the node to be deleted
 * real work is done by delete_proper_helper
 */
void delete_proper(Node_handle* ppRoot,int key) {
	struct Node *p_delete = *ppRoot;

	/*empty tree case - do nothing*/
	if ( !*ppRoot ) return;

	/*find node to delete*/
	while (p_delete && p_delete->key!=key) {
		if (p_delete->key<key) {
			p_delete = p_delete->right;
		}
		else {
			p_delete = p_delete->left;
		}
	}

	if (!p_delete) return;
	else delete_proper_helper(p_delete,ppRoot);
}

void delete_proper_helper(Node_handle p_delete, Node_handle* ppRoot) {
	struct Node *parent = getparent(p_delete);
	enum Dir {left,right,root} dir;

	/* need to know whether the deleted node is left or right child */
	if ( parent == NULL) dir = root;
	else                 dir = (getleft(parent)==p_delete)?left:right;

	/* ... */
}

void delete(Node_handle* ppRoot,int key) {
	struct Node *p_delete = *ppRoot;

	/*find node to delete*/
	while (p_delete && p_delete->key!=key) {
		if (p_delete->key<key) p_delete = p_delete->right;
		else                   p_delete = p_delete->left;
	}

	/* key doesn't exist */
	if (!p_delete) return;
	else {
		struct Node *parent = getparent(p_delete);
		enum Dir {left,right,root} dir;

		/* need to know whether the deleted node is left or right child */
		if ( parent == NULL) dir = root;
		else                 dir = (getleft(parent)==p_delete)?left:right;

	}
	/* ... */
}

Node_handle find_recursive(Node_handle const pRoot, int key) {
	if (!pRoot) return 0;

	if (pRoot->key==key) return pRoot;
	else {
		if (pRoot->key<key) return find_recursive(pRoot->right,key);
		else                  return find_recursive(pRoot->left,key);
	}
}

Node_handle find_iterative(Node_handle const pRoot, int key) {
	struct Node* curr=pRoot;

	while (curr) {
		if (key==curr->key ) return curr;
		/*printf("at %d\n",curr->key);*/

		if (key<curr->key ) {
			/*printf("check left\n");*/
			curr=curr->left; 
		} else {
			/*printf("check right\n");*/
			curr=curr->right;
		}
	}

	return 0;
}

void print_recursive(Node_handle const pRoot) {
	if (pRoot) {
		print_recursive(pRoot->left);
		printf ("%d -> %d;  ",pRoot->key,pRoot->value);
		print_recursive(pRoot->right);
	}
}

void delete_tree(Node_handle pRoot) {
}

Node_handle first(Node_handle pRoot) {
	if (!pRoot) return 0;
	while (pRoot->left) pRoot = pRoot->left;
	return pRoot;
}

Node_handle last(Node_handle pRoot) {
}

Node_handle increment(Node_handle it) {
	if (!it) { return it; }
	/* Find leftmost child in right subtree
	   This is the successor of it
	   */
	if (it->right) {
		struct Node *p = it->right;
		while (p->left) p = p->left;
		it = p;
	}
	else {
		/* Walk up the tree to find the successor of it
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

Node_handle decrement(Node_handle it) {
}

