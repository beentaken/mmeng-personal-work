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
		int Count(void);
		void Insert(int value, int position);
		struct Node *FindItem(int value);
		void Delete(int value);
		void Concat(const List &toConcat);
		void Delete(List &toDelete);
		void Insert(int value);

		friend std::ostream &operator<<(std::ostream &lhs, const List &rhs);

	private:

		Node* head_;
		Node* MakeNode(int value);

		void AddToEnd(struct Node **ppList, int value);
		void AddToFront(struct Node **ppList, int value);
		int Count(struct Node *list);
		void PrintList(struct Node *list);
		void Insert(struct Node **ppList, int value, int position);
		struct Node *FindItem(struct Node *list, int value);
		void Delete(struct Node **ppList, int value);
		void Concat(struct Node **Destination, struct Node *Source);
		void Delete(struct Node **ppList, struct Node *Items);
		void Insert(struct Node **ppList, int value);
	
		void FreeList(struct Node *pList);
};

#endif // LIST_H
