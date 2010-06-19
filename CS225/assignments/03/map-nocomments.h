/* file_header_comment */

#ifndef MAP_H
#define MAP_H

#include <fstream>

namespace CS225 {
	class Map {
		private:
			class Node {
				public:
					Node(int k,int val,Node* p,Node* l,Node* r);
					int Key() const;
					//useful methods, used only bu Map implementation, so you
					//may change them or add your own
					Node*  first();
					Node*  last();
					Node*  increment();
					Node*  decrement();
					Node*  find(int key);
				public: //normally this would be private, but in our case Node
						//is an inner class of Map AND there is no method that
						//returns Node to the client, so overall client will
						//never be able to access data, thus it's OK to make it
						//public. Otherwise (if it's private) declare Map and
						//Map_iterator as friends, since they need access to
						//key and value
					int    key;
					int    value;
					Node   *parent;
					Node   *left;
					Node   *right;
				private:
					//the following methods should NOT be used, declare them in
					//the private area adn DO NOT implement thus we make sure
					//that compiler doesn't generate automatic versions of
					//these methods (which someone may accidentally use and
					//break something)
					Node(const Node&);
					Node* operator=(const Node&);
					//You may implement public copy and assignment, but I
					//didn't find it useful.
			};

			class Map_iterator {
				private:
					Node* p_node;
				public:
					Map_iterator(Node* p);
					//automatic version of copy ctor and assign operator are OK
					Map_iterator& operator++();
					Map_iterator operator++(int);
					int& operator*(); //returns non-const - data may be modified
					const int& Key() const; //returns const - WHY???
					bool operator!=(const Map_iterator& rhs) const;
					bool operator==(const Map_iterator& rhs) const;
					friend class Map;
			};

			class Map_iterator_const {
				private:
					Node* p_node;
				public:
					Map_iterator_const(Node* p);
					//automatic version of copy ctor and assign operator are OK
					Map_iterator_const& operator++();
					Map_iterator_const operator++(int);
					const int& operator*();
					const int& Key() const;
					bool operator!=(const Map_iterator_const& rhs) const;
					bool operator==(const Map_iterator_const& rhs) const;
					friend class Map;
			};

			Node* pRoot;
			//end iterators are same for all Maps, thus static.  make
			//Map_iterator a friend to allow Map_iterator to access end
			//iterators 
			static Map_iterator end_it;
			static Map_iterator_const const_end_it;

		public:
			//BIG FOUR
			Map();
			Map(const Map& rhs);
			Map& operator=(const Map& rhs);
			virtual ~Map();

			//value setter and getter
			int& operator[](int key);
			//next method doesn't make sense because operator[] inserts 0,
			//which is not allowed on const maps 
			//int operator[](int key) const;

			//standard names for iterator types, not required.
			typedef Map_iterator       iterator;
			typedef Map_iterator_const const_iterator;

			//Map methods dealing with non-const iterator 
			Map_iterator begin();
			Map_iterator end();
			Map_iterator find(int key);
			void erase(Map_iterator it);

			//Map methods dealing with const iterator 
			Map_iterator_const begin() const;
			Map_iterator_const end() const;
			Map_iterator_const find(int key) const;
			//do not need this one (why)
			//Map_iterator_const erase(Map_iterator& it) const;

			void print(std::ostream& os) const;
			
			//inner class (Map_iterator) doesn't have any special priveleges in
			//accessing private data/methods of the outer class (Map) so we need
			//friendship to allow Map_iterator to access private "Map::end_it"
			//BTW - same is true for outer class accessing inner class private
			//data
			friend class Map_iterator;
			friend class Map_iterator_const;
		private:
			//helper methods
			//add your stuff here
			void my_copy_recursive(Node **current, Node *rhs, Node *new_parent);
			void delete_nodes(Node * current);
			void delete_proper_helper(Node * p_delete, Node ** ppRoot);
			Node* insert_iterative(Node **ppRoot, int key, int value);

			//need next 2 for pretty printing
			int   getdepth(const Node* node) const;
			char  getedgesymbol(const Node* node) const;
	};

	//notice that it doesn't need to be friend
	std::ostream& operator<<(std::ostream& os, const Map& map);
}

#endif

