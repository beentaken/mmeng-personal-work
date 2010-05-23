#include "map.h"
#include <stdio.h>
#include <stdlib.h>

/* strict C doesn't allow declaration to substitute prototype */
void print_forwards(Node_handle pRoot);
void print_backwards(Node_handle pRoot);
void print_padded(Node_handle pRoot, int padding, char edge);
int getdepth(Node_handle node);
char getedgesymbol(Node_handle node);
void print_backwards_padded(Node_handle pRoot);
Node_handle build_tree_iterative(void);
Node_handle build_tree_recursive(void);
Node_handle complete_binary_tree(int n);
void test0(void);
void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);
void test7(void);
void test8(void);
void test9(void);
void test10(void);
void test11(void);
void test12(void);
void test13(void);
void test14(void);
void test15(void);
void test16(void);
void test17(void);
void test18(void);
void test19(void);
void test20(void);
void permute(int *v, int start, int n, const int * const values);
	
void print_forwards(Node_handle pRoot) {
	Node_handle b = first(pRoot);
	while ( b  ) { 
		printf ("%d -> %d;  ",getkey(b),getvalue(b));
		b = increment(b); 
	}
	printf("\n");
}

void print_backwards(Node_handle pRoot) {
	Node_handle b = last(pRoot);
	while ( b ) { 
		printf ("%d -> %d;  ",getkey(b),getvalue(b));
		b = decrement(b);
	}
	printf("\n");
}

/* this is a "ASCII-graphical" print
 * recursive function. 
 * Left branch of the tree is at the top !!!
 */
void print_padded(Node_handle pRoot, int padding, char edge) {
	if (pRoot) {
		int i=0;
		print_padded(getleft(pRoot), padding + 5,'/');
		for (; i<padding; ++i) printf(" ");
		printf ("%c %d\n",edge,getvalue(pRoot));
		print_padded(getright(pRoot), padding + 5,'\\');
	}
}

/* returns the depth of the node, used in print_backwards_padded */
int getdepth(Node_handle node) {
	int d = -1;
	while ( node ) { 
		++d; 
		node=getparent(node);
	}
	return d;
}

/* figure out whether node is left or right child or root 
 * used in print_backwards_padded 
 */
char getedgesymbol(Node_handle node) {
	Node_handle parent = getparent(node);
	if ( parent == NULL) return '-';
	else                 return (getleft(parent)==node)?'\\':'/';
}

/* this is another "ASCII-graphical" print, but using 
 * iterative function. 
 * Left branch of the tree is at the bottom
 */
void print_backwards_padded(Node_handle pRoot) {
	Node_handle b = last(pRoot);
	while ( b ) { 
		int depth = getdepth(b);
		int i;
		/* printf(b); */

		char edge = getedgesymbol(b);
		switch (edge) {
			case '-': 
				for (i=0; i<depth; ++i) printf("    ");
				printf("%d\n",getvalue(b));
				break;
			case '\\': 
				for (i=0; i<depth; ++i) printf("    ");
				printf("%c\n",edge);
				for (i=0; i<depth; ++i) printf("    ");
				printf("  %d\n",getvalue(b));
				break;
			case '/': 
				for (i=0; i<depth; ++i) printf("    ");
				printf("  %d\n",getvalue(b));
				for (i=0; i<depth; ++i) printf("    ");
				printf("%c\n",edge);
				break;
		}
		b = decrement(b);
	}
	printf("\n");
}

/* creates a map
 * for simplicity key and value are the same integer
 */
Node_handle build_tree_iterative(void) {
	Node_handle pRoot=0;
	int values[] = {6,5,10,3,4,1,12,15,13,18};
	unsigned i;

	for (i=0;i<sizeof(values)/sizeof(values[0]); ++i) {
		if ( insert_iterative(&pRoot,values[i],values[i]) ) { printf("Error on line %d\n",__LINE__); }
	}

	return pRoot;
}

/* creates a map
 * for simplicity key and value are the same integer
 */
Node_handle build_tree_recursive(void) {
	Node_handle pRoot=0;
	int values[] = {6,5,10,3,4,1,12,15,13,18};
	unsigned i;

	for (i=0;i<sizeof(values)/sizeof(values[0]); ++i) {
		if ( insert_recursive(&pRoot,values[i],values[i]) ) { printf("Error on line %d\n",__LINE__); }
	}

	return pRoot;
}

/* builds a complete binary tree of height n
 * obviously doesn't work when n>31
 */
Node_handle complete_binary_tree(int n) {
	Node_handle pRoot=0;
	int depth = 0;
	int step = 1 << (n-1);
	int max = (1 << n);

	for (; depth<n && step>0; ++depth, step = (step >> 1)) {
		int i = step;
		for ( ; i<max ; i+=step ) {
			if ( insert_recursive(&pRoot,i,i) == E_NO_MEMORY ) { 
				printf("Error\n"); 
			}
		}
	}

	return pRoot;
}

void test0(void) {
	Node_handle pRoot = build_tree_iterative(), node;
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	print_backwards_padded(pRoot);

	node = find_iterative( pRoot, 15 );
	if (node==NULL) printf("Error on line %d\n",__LINE__);
	else setvalue(node,1155);
	node = find_iterative( pRoot, 1 );
	if (node==NULL) printf("Error on line %d\n",__LINE__);
	else setvalue(node,1111);
	node = find_iterative( pRoot, 11 );
	if (node!=NULL) printf("Error on line %d\n",__LINE__);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	print_backwards_padded(pRoot);

	delete_tree(pRoot);
}

void test1(void) {
	Node_handle pRoot = build_tree_recursive(), node;
	print_recursive(pRoot); printf("\n");
	print_forwards(pRoot); printf("\n");
	print_backwards(pRoot); printf("\n");
	print_padded(pRoot,0,'-');
	
	node = find_recursive( pRoot, 15 );
	if (node==NULL) printf("Error on line %d\n",__LINE__);
	else 	setvalue(node,1155);
	node = find_recursive( pRoot, 1 );
	if (node==NULL) printf("Error on line %d\n",__LINE__);
	else 	setvalue(node,1111);
	node = find_iterative( pRoot, 11 );
	if (node!=NULL) printf("Error on line %d\n",__LINE__);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	print_backwards_padded(pRoot);

	delete_tree(pRoot);
}

void test2(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	/* print in both directions to test ALL links */
	delete(&pRoot,4);
	printf("delete 4\n");
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("delete 1\n");
	delete(&pRoot,1);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test3(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 15\n");
	delete(&pRoot,15);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test4(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 12\n");
	delete(&pRoot,12);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test5(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 6\n");
	delete(&pRoot,6); 
	print_forwards(pRoot); 
	printf("------------------------------\n");
	print_backwards(pRoot);
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test6(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 122\n");
	delete(&pRoot,122); /* non-existing key */
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}


void test7(void) {
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 5\n");
		delete(&pRoot,5); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 6\n");
		delete(&pRoot,6); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
}

void test8(void) {
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 6\n");
		delete(&pRoot,6); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 5\n");
		delete(&pRoot,5); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
}

void test9(void) {
	int depth = 5;
	Node_handle pRoot = complete_binary_tree(depth);
	int i = 1;
	print_padded(pRoot,0,'-');
	for ( ; i < 1<<depth; ++i) {
		printf("deleting key %d \n",i);
		delete(&pRoot,i);
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
	}
	print_padded(pRoot,0,'-');
	delete_tree(pRoot);
}

void test10(void) {
	int depth = 3;
	Node_handle pRoot = complete_binary_tree(depth);
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	print_backwards_padded(pRoot);
	printf("------------------------------\n");
	
	printf("delete 4\n");
	delete(&pRoot,4);

	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	print_backwards_padded(pRoot);
	delete_tree(pRoot);
}

/* same tests 2-10, but using delete_proper instead of delete */
void test11(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	/* print in both directions to test ALL links */
	delete_proper(&pRoot,4);
	printf("delete 4\n");
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("delete 1\n");
	delete_proper(&pRoot,1);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test12(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 15\n");
	delete_proper(&pRoot,15);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test13(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 12\n");
	delete_proper(&pRoot,12);
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test14(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 6\n");
	delete_proper(&pRoot,6); 
	print_forwards(pRoot); 
	printf("------------------------------\n");
	print_backwards(pRoot);
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}

void test15(void) {
	Node_handle pRoot = build_tree_recursive();
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	/* print in both directions to test ALL links */
	printf("delete 122\n");
	delete_proper(&pRoot,122); /* non-existing key */
	print_recursive(pRoot); printf("\n");
	printf("------------------------------\n");
	print_forwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_backwards(pRoot); printf("\n");
	printf("------------------------------\n");
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	delete_tree(pRoot);
}


void test16(void) {
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 5\n");
		delete_proper(&pRoot,5); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 6\n");
		delete_proper(&pRoot,6); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
}

void test17(void) {
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 6\n");
		delete_proper(&pRoot,6); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
	{
		Node_handle pRoot = 0;
		if ( insert_iterative(&pRoot,5,5) ) { printf("Error\n"); }
		if ( insert_iterative(&pRoot,6,6) ) { printf("Error\n"); }
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		/* print in both directions to test ALL links */
		printf("delete 5\n");
		delete_proper(&pRoot,5); 
		print_forwards(pRoot); 
		printf("------------------------------\n");
		print_backwards(pRoot);
		printf("------------------------------\n");
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
		delete_tree(pRoot);
	}
}

void test18(void) {
	int depth = 5;
	Node_handle pRoot = complete_binary_tree(depth);
	int i = 1;
	print_padded(pRoot,0,'-');
	for ( ; i < 1<<depth; ++i) {
		printf("deleting key %d \n",i);
		delete_proper(&pRoot,i);
		print_padded(pRoot,0,'-');
		printf("------------------------------\n");
	}
	print_padded(pRoot,0,'-');
	delete_tree(pRoot);
}

void test19(void) {
	int depth = 3;
	Node_handle pRoot = complete_binary_tree(depth);
	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	print_backwards_padded(pRoot);
	printf("------------------------------\n");
	
	printf("delete 4\n");
	delete_proper(&pRoot,4);

	print_padded(pRoot,0,'-');
	printf("------------------------------\n");
	print_backwards_padded(pRoot);
	delete_tree(pRoot);
}

void permute(int *v, int start, int n, const int * const values) {
	if (start == n-1) {
		/* permutation is ready */
		Node_handle pRoot=0;
		int i;

		/* insert values - same order each time, see test20 */
		for (i=0;i<n; ++i) {
			if ( insert_iterative(&pRoot,values[i],values[i]) ) { printf("Error on line %d\n",__LINE__); }
		}
		/* delete values in the order of the current permutation */
		for (i=0;i<n; ++i) {
			delete_proper(&pRoot,v[i]);
		}
		print_forwards(pRoot); /* should be empty */

		/* since the tree should be empty, there is no need to delete it */
	}
	else {
		/* the core algorithm for building permutations */
		int i;
		for (i = start; i < n; ++i) {
			/* swap v[i] and v[start] */
			int tmp = v[i];
			v[i] = v[start];
			v[start] = tmp;
			/* call recursively with shifted start */
			permute(v, start+1, n, values);
			/* swap v[i] and v[start] again */
			v[start] = v[i];
			v[i] = tmp;
		}
	}
}


void test20(void) {
	/* sort of a stress test - given a tree, delete nodes 
	 * in all possible orders. 
	 * Permutations are implemented in permute,
	 */
	int insert_values[] = {4, 2, 3, 1, 5, 6};
	/* so each time we work with this tree
	 *               4
	 *              / \ 
	 *             2   5
	 *            / \   \
	 *           1   3   6
	 */
	int v[] = {1, 2, 3, 4, 5, 6};
	/* there are 6!=720 possible permutation 
	 * so the output of this test is 720 empty lines
	 */
	permute(v, 0, sizeof(v)/sizeof(v[0]),insert_values);
}

void (*pTests[])(void) = { 
	test0, test1, test2, test3, test4, test5, test6, 
	test7, test8, test9, test10, test11, test12, test13, 
	test14, test15, test16, test17, test18, test19, test20 };

int main(int argc, char *argv[] ) {
  if (argc!=2) return 1;
	pTests[atoi(argv[1])]();
  return 0;
}
