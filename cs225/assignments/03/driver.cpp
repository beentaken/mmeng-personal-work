#include "map.h"
#include <iostream>
#include <cstdlib> /* atoi */


/* builds a complete binary tree of height n
 * obviously doesn't work when n>31
 */
CS225::Map complete_binary_tree(int n) {
	CS225::Map map;
	int depth = 0;
	int step = 1 << (n-1);
	int max = (1 << n);

	for (; depth<n && step>0; ++depth, step = (step >> 1)) {
		int i = step;
		for ( ; i<max ; i+=step ) {
			map[i]=i;
		}
	}

	return map;
}

void test0(void) {
	CS225::Map map;
	map[1]=1;
	std::cout << "-------\n" << map << "-------\n" << std::endl;
	map[2]=2;
	std::cout << "-------\n" << map << "-------\n" << std::endl;
	map[0]=0;
	std::cout << "-------\n" << map << "-------\n" << std::endl;
	std::cout << map;
}

void test1(void) {
	CS225::Map map;
	map[1]=1;
	map[2]=2;
	map[0]=0;
	std::cout << "---ORIGINAL----\n" << map << "-------\n" << std::endl;

	CS225::Map::iterator it = map.find(1);
	//it->key = 100;
	std::cout << "---RESULT----\n" << *it << "-------\n" << std::endl;
	*it=1000;
	std::cout << "---MODIFIED ORIGINAL----\n" << map << "-------\n" << std::endl;
}

void test2(void) {
	CS225::Map map;
	map[1]=1;
	map[2]=2;
	map[0]=0;
	std::cout << "---ORIGINAL----\n" << map << "-------\n" << std::endl;

	CS225::Map::iterator it = map.find(2);
	map.erase(it);
	std::cout << "---RESULT----\n" << map << "-------\n" << std::endl;
}

void test3(void) {
	CS225::Map map = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map << "-------\n" << std::endl;

	CS225::Map::iterator b = map.begin(), e = map.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
	}
}

void test4(void) {
	CS225::Map map1 = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	CS225::Map map2(map1);
	std::cout << "---COPY----\n" << map2 << "-------\n" << std::endl;

	CS225::Map::iterator b = map2.begin(), e = map2.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
	}
}

void test5(void) {
	CS225::Map map1 = complete_binary_tree(3);
	CS225::Map map2 = complete_binary_tree(4);
	std::cout << "---ORIGINAL 1----\n" << map1 << "-------\n" << std::endl;
	std::cout << "---ORIGINAL 2----\n" << map2 << "-------\n" << std::endl;
	map2 = map1;
	std::cout << "---AFTER ASSIGNMENT----\n" << map2 << "-------\n" << std::endl;

	CS225::Map::iterator b = map2.begin(), e = map2.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
	}
}

void test6(void) {
	CS225::Map map1 = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	CS225::Map map2(map1);
	std::cout << "---COPY----\n" << map2 << "-------\n" << std::endl;
	std::cout << "---MODIFY COPY----\n";
	map2[11]=11;
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	std::cout << "---COPY----\n" << map2 << "-------\n" << std::endl;
}

void test7(void) {
	CS225::Map map1 = complete_binary_tree(3);
	CS225::Map map2 = complete_binary_tree(4);
	std::cout << "---ORIGINAL 1----\n" << map1 << "-------\n" << std::endl;
	std::cout << "---ORIGINAL 2----\n" << map2 << "-------\n" << std::endl;
	map2 = map1;
	std::cout << "---AFTER ASSIGNMENT----\n" << map2 << "-------\n" << std::endl;
	std::cout << "---MODIFY COPY----\n";
	map2[11]=11;
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	std::cout << "---COPY----\n" << map2 << "-------\n" << std::endl;
}

void test8(void) {
	CS225::Map map1 = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	const CS225::Map map2(map1);
	std::cout << "---CONST COPY----\n" << map2 << "-------\n" << std::endl;

	/* //this code SHOULD NOT compile
	   CS225::Map::iterator b = map2.begin(), e = map2.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
	}
	*/

	CS225::Map::const_iterator b = map2.begin(), e = map2.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
	}
}

void test9(void) {
	CS225::Map map1 = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;

	CS225::Map::iterator b = map1.begin(), e = map1.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
		*b += 100;
	}
	
	std::cout << "---MODIFIED ORIGINAL----\n" << map1 << "-------\n" << std::endl;
}

void test10(void) {
	CS225::Map map1 = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	const CS225::Map map2(map1);
	std::cout << "---CONST COPY----\n" << map2 << "-------\n" << std::endl;

	/* //this code SHOULD NOT compile
	   CS225::Map::iterator b = map2.begin(), e = map2.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
		*b += 100;
	}
	
	std::cout << "---MODIFIED ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	*/
}

void test11(void) {
	CS225::Map map1 = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;

	CS225::Map::iterator b = map1.begin();
	while ( b!=map1.end() ) {
		std::cout << "erase " << *b << std::endl;
		map1.erase(b);
		std::cout << "---MODIFIED ORIGINAL----\n" 
			<< map1 << "-------\n" << std::endl;
		b = map1.begin();
	}
	
}

void test12(void) {
	CS225::Map map1 = complete_binary_tree(3);
	CS225::Map::iterator b = map1.begin(), e = map1.end();
	for ( ; b!=e; ++b) { *b += 100; }
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;
	
	for (int i=1; i<7; ++i) {
		std::cout << i << " -> " << map1[i] << std::endl;
	}
}

void test13(void) {
	for (int f = 1; f<7; ++f) {
		CS225::Map map;
		for (int i=1; i<7; ++i) { map[(i*f)%7+1] = ((i*f)%7+1)*((i*f)%7+1); }
		std::cout << "---MAP----\n" << map << "-------\n" << std::endl;
	}
}

void test14(void) {
	CS225::Map map1 = complete_binary_tree(3);
	std::cout << "---ORIGINAL----\n" << map1 << "-------\n" << std::endl;

	CS225::Map::iterator b = map1.begin();
	while ( b!=map1.end() ) {
		//using operator-> to access key (b->Key()) 
		//make sure you understand which operator-> is called

		//The 2 lines implement different logic
		//std::cout << b.Key() << " ---> " << *(b++) << std::endl;
		std::cout << b.Key() << " ---> "; std::cout << *(b++) << std::endl;
		//in the first line "++" is called before  b.Key(); (GNU).
		//So operator >> is similar to printf in the sense that the order of
		//operations is not defined.
		// here is debug output for both lines (GNU)
		// windows and/or borland may have different order for the first line!!!
		//------------------------------------------------------------
		//std::cout << b.Key() << " ---> " << *(b++) << std::endl;
		//------------------------------------------------------------
		//enter CS225::Map::Map_iterator CS225::Map::Map_iterator::operator++(int)
		//enter CS225::Map::Node* CS225::Map::Node::increment()
		//leaving CS225::Map::Node* CS225::Map::Node::increment()
		//leaving CS225::Map::Map_iterator CS225::Map::Map_iterator::operator++(int)
		//enter int& CS225::Map::Map_iterator::operator*()
		//leaving int& CS225::Map::Map_iterator::operator*()
		//enter CS225::Map::Node* CS225::Map::Map_iterator::operator->()
		//leaving CS225::Map::Node* CS225::Map::Map_iterator::operator->()
		//enter int CS225::Map::Node::Key() const
		//leaving int CS225::Map::Node::Key() const
		//2 ---> 1

		//------------------------------------------------------------
		//std::cout << b.Key() << " ---> "; std::cout << *(b++) << std::endl;
		//------------------------------------------------------------
		//enter CS225::Map::Node* CS225::Map::Map_iterator::operator->()
		//leaving CS225::Map::Node* CS225::Map::Map_iterator::operator->()
		//enter int CS225::Map::Node::Key() const
		//leaving int CS225::Map::Node::Key() const
		//1 ---> 
		//enter CS225::Map::Map_iterator CS225::Map::Map_iterator::operator++(int)
		//enter CS225::Map::Node* CS225::Map::Node::increment()
		//leaving CS225::Map::Node* CS225::Map::Node::increment()
		//leaving CS225::Map::Map_iterator CS225::Map::Map_iterator::operator++(int)
		//enter int& CS225::Map::Map_iterator::operator*()
		//leaving int& CS225::Map::Map_iterator::operator*()
		//1


	}
}

void test15(void) {
	CS225::Map map;
	std::cout << "---PRINTING AN EMPTY MAP----\n" << map << "-------\n" << std::endl;
	
	CS225::Map::iterator b = map.begin(), e = map.end();
	for ( ; b!=e; ++b) {
		std::cout << *b << std::endl;
	}
	const CS225::Map cmap;
	std::cout << "---PRINTING AN EMPTY MAP----\n" << cmap << "-------\n" << std::endl;
	
	CS225::Map::const_iterator cb = cmap.begin(), ce = cmap.end();
	for ( ; cb!=ce; ++cb) {
		std::cout << *cb << std::endl;
	}
}

void permute(int *v, int start, int n, const int * const values) {
	if (start == n-1) {
		/* permutation is ready */
		CS225::Map map;

		/* insert values - same order each time, see test15 */
		for (int i=0;i<n; ++i) {
			map[values[i]]=values[i];
		}
		/* delete values in the order of the current permutation */
		for (int i=0;i<n; ++i) {
			map.erase( map.find(v[i]) );
		}
		std::cout << map;

		/* since the tree should be empty, there is no need to delete it */
	}
	else {
		/* the core algorithm for building permutations */
		for (int i = start; i < n; ++i) {
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


void test16(void) {
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
	 * so the output of this test is 720 empty lines !!!
	 */
	permute(v, 0, sizeof(v)/sizeof(v[0]),insert_values);
}

void test17(void);

void (*pTests[])(void) = { 
	test0, test1, test2, test3, test4, test5, test6, 
	test7, test8, test9, test10, test11, test12, test13, 
	test14, test15, test16, test17
};

void test17() {
	for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0])-1; ++i)
		pTests[i]();
}

int main(int argc, char *argv[] ) {
  if (argc!=2) return 1;
	pTests[std::atoi(argv[1])]();
  return 0;
}
