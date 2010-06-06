#ifndef MAP_H
#define MAP_H

enum {E_NO_MEMORY = 1};

/* opaque pointer
 * since definition of Node is hidden from the client
 * we need to provide some way to use Node struct,
 * and here it is -- typedef. 
 * At this point Node is NOT KNOWN to the compiler (which makes Node
 * an INCOMPLETE TYPE, but declaring a pointer to an incomplete type 
 * is allowed by C (and C++).
 *
 * see http://en.wikipedia.org/wiki/Opaque_pointer
 */
typedef struct Node* Node_handle;

int  insert_recursive(Node_handle* ppRoot, int key, int value); 
int  insert_iterative(Node_handle* ppRoot, int key, int value);

void delete(Node_handle* ppRoot,int key);
void delete_proper(Node_handle* ppRoot,int key); /*implemented*/
void delete_proper_helper(Node_handle pp_delete,Node_handle* ppRoot);
void delete_silly(Node_handle* ppRoot,int key); /*implemented*/

Node_handle find_recursive(Node_handle const pRoot, int key); /*implemented*/
Node_handle find_iterative(Node_handle const pRoot, int key); /*implemented*/

void print_recursive(Node_handle const pRoot); /*implemented*/

void delete_tree(Node_handle pRoot);

int getkey (Node_handle const node);  /*implemented*/
int getvalue(Node_handle const node);
Node_handle getleft (Node_handle const node);
Node_handle getright(Node_handle const node);
Node_handle getparent(Node_handle const node);

void print(Node_handle node); /*implemented*/

void setvalue(Node_handle node, int newvalue);

/* REsetting a position is prohibited, since
 * it will break the "binary-tree" property
 *
 * void setkey(Node_handle node, int newkey);
 *
 * one should 
 * 1) delete node at the old position
 * 2) insert a new node at the new position
 * both function are already implemented
 */

Node_handle first(Node_handle it); /*implemented*/
Node_handle last(Node_handle it);

Node_handle increment(Node_handle it); /*implemented*/
Node_handle decrement(Node_handle it);

#endif

