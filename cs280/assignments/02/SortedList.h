//---------------------------------------------------------------------------
#ifndef SORTEDLISTH
#define SORTEDLISTH
//---------------------------------------------------------------------------

#include <string>     // error strings
#include <stdexcept>  // std::exception
#include <functional> // std::less

#include "ObjectAllocator.h"

//#define MARCUS_DEBUG
#ifdef MARCUS_DEBUG
#include <iostream>
#endif

class SortedListException : public std::exception
{
  private:  
    int m_ErrCode;
    std::string m_Description;

  public:
    SortedListException(int ErrCode, const std::string& Description) :
    m_ErrCode(ErrCode), m_Description(Description) {};

    virtual int code(void) const { 
      return m_ErrCode; 
    }

    virtual const char *what(void) const throw() {
      return m_Description.c_str();
    }

    virtual ~SortedListException() throw() {
    }

    enum SORTEDLIST_EXCEPTION {E_NO_MEMORY, E_DATA_ERROR};
};

template <typename T, typename Pred = std::less<T> >
class SortedList
{
  struct Node;
  public:
      // Constructor
    SortedList(Pred sorter = std::less<T>(), ObjectAllocator *Allocator = 0, bool SharedAllocator = false);

      // Copy constructor
    SortedList(const SortedList &rhs) throw(SortedListException);

      // Destructor
    ~SortedList() throw();
      
      // Assignment operator
    SortedList& operator=(const SortedList &rhs) throw(SortedListException);

    void push_back(const T& value) throw(SortedListException);
    void insert(const T& value) throw(SortedListException);
    unsigned size(void) const throw();
    void clear(void) throw();

    template <typename Sorter>
    void selection_sort(Sorter sorter = std::less<T>()); 

    template <typename Sorter>
    void merge_sort(Sorter sorter = std::less<T>());

    static bool ImplementedExtraCredit(void);

    static unsigned nodesize(void);

    //**************************************************
    // const_iterator
    class const_iterator
    {
      public:
        const_iterator(Node *p);                          // conversion ctor
        const T& operator*(void) const;                   // dereference op
        const_iterator& operator++(void);                 // pre-increment
        const_iterator& operator--(void);                 // pre-decrement
        bool operator!=(const const_iterator &rhs) const; // inequality op
      private:
        Node* current_; // pointer to the current node
    };
    //**************************************************

      // iteration
    const_iterator begin(void) const;  // the first node
    const_iterator end(void) const;    // one past the end
    const_iterator rbegin(void) const; // the last node
    const_iterator rend(void) const;   // one before the first

  private: // Suggestions...
    struct Node
    {
      Node *Next;
      Node *Prev;
      T Data;
      Node(const T& data) : Data(data) {}
    };

    ObjectAllocator *objAllocator_;
    Pred sorter_;
    bool shareAllocator_;
    bool freeAllocator_;
    Node *head_;
    Node *tail_;
    unsigned size_;
    
    // Other private fields and methods ...

    // Construction stuff.
    Node* allocNode() throw(SortedListException);
    Node* createNode(const T& value) throw(SortedListException);
    ObjectAllocator* createAllocator(OAConfig &new_config) throw(SortedListException);

    // Cleanup stuff.
    void destroyAllNodes(Node* current);
    void destroyAllocator();

    // Internal utilities.
    void copyNodes(const SortedList<T, Pred> &rhs);
    void insertNode(Node* current, const T& value);
    void swapNodes(Node* first, Node* second);
    template<typename Sorter>
    Node* findMinNode(Node* current, Node* min, const Sorter &sorter);
    void advanceNode(Node* &current, unsigned to_advance);

    // Node manipulation.
    Node* extractNode(Node* to_remove);
    void insertAfterNode(Node* to_insert, Node* position);
    void moveNode(Node* to_move, Node* destination);
    template<typename Sorter>
    Node* merge_lists(Node* list1, unsigned length1, Node* list2, unsigned length2, const Sorter &sorter);
    template<typename Sorter>
    Node* merge_sort_helper(Node* current, unsigned chunk_size, const Sorter &sorter);

    // Debugging, ugh.
#ifdef MARCUS_DEBUG
    void print_nodes(Node* current, unsigned length);
#endif
};

#include "SortedList.cpp"

#endif

