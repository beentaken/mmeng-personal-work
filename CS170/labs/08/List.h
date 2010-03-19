////////////////////////////////////////////////////////////////////////////////
#ifndef LIST_H
#define LIST_H
////////////////////////////////////////////////////////////////////////////////

struct Node
{
	int number; // data portion
	Node *next; // pointer portion

	Node(int value);
	friend std::ostream &operator<<(std::ostream &lhs, const Node *rhs);
};

class List
{
	public:
		List(void);
		~List(void);

		void AddToEnd(int value);
		void AddToFront(int value);
		int Count(void) const;
		void Insert(int value, int position);
		struct Node *FindItem(int value) const;
		void Delete(const int value);
		void Concat(const List &toConcat);
		void Delete(const List &toDelete);
		void Insert(int value);

		void Merge(List& rhs);

		int RemoveDuplicates(void);

		friend std::ostream &operator<<(std::ostream &lhs, const List &rhs);

	private:

		Node* head_;
		Node* MakeNode(int value);

		void AddToEnd(struct Node **ppList, int value);
		void AddToFront(struct Node **ppList, int value);
		int Count(struct Node *list) const;
		void PrintList(struct Node *list) const;
		void Insert(struct Node **ppList, int value, int position);
		struct Node *FindItem(struct Node *list, int value) const;
		void Delete(struct Node **ppList, int value);
		void Concat(struct Node **Destination, struct Node *Source);
		void Delete(struct Node **ppList, struct Node *Items);
		void Insert(struct Node **ppList, int value);
		void Merge(struct Node **ppList, struct Node** toAdd);
	
		void FreeList(struct Node *pList);
};

#endif // LIST_H
