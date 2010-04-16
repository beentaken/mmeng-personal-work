////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{

class SubscriptError
{
	public:
		SubscriptError(int Subscript) : subscript_(Subscript) {};
		int GetSubscript(void) const { return subscript_; }
	private:
		int subscript_;
};

class Vector
{
  public:
	struct SortResult
	{
		unsigned compares;
		unsigned swaps;
	};



      // Default constructor
    Vector(void);

      // Destructor
    ~Vector();

      // Copy constructor
    Vector(const Vector& rhs);

      // Constructor to create a Vector from an array
    Vector(const int array[], unsigned size);

      // Adds a node to the front of the list
    void push_back(int value);

      // Adds a node to the end of the list
    void push_front(int value);

      // Removes the last element. Does nothing if empty.
    void pop_back(void);

      // Removes the first element. Does nothing if empty.
    void pop_front(void);

      // Inserts a new node at the specified position. Causes an
      // abort() if the position is invalid.
    void insert(int value, unsigned position);

      // Removes an element with the specified value (first occurrence)
    void remove(int value);

      // Finds an item (first occurrence) and returns the index 
      // where it was found
    int find(int value) const;

    void pack(void);

      // Deletes the underlying array and sets size_ to 0
    void clear(void);

      // Return true if the vector is empty, otherwise, false
    bool empty(void) const;

    SortResult selection_sort(void);
    SortResult bubble_sort(void);
    int bsearch(int value) const;

      // Assignment operator
    Vector& operator=(const Vector& rhs);

      // Concatenates a vector onto the end of this vector.
    Vector& operator+=(const Vector& rhs);

      // Concatenates two Vectors.
    Vector operator+(const Vector& rhs) const;

      // Subscript operators.
    int operator[](unsigned index) const;
    int& operator[](unsigned index);

      // Returns the number of elements in the vector.
    unsigned size(void) const;

      // Returns the size of the underlying array
    unsigned capacity(void) const;

      // The number of memory allocations that have occurred
    unsigned allocations(void) const;

    // Reverses the order of the elements (Linear time)
    void reverse(void);

    // Swaps the contents of this Vector with another (constant time)
    void swapv(Vector &other);

    // Equality operator (linear time)
    bool operator==(const Vector &rhs) const;

  private:
    int *array_;        // The dynamically allocated array
    unsigned size_;     // The number of elements in the array
    unsigned capacity_; // The allocated size of the array
    unsigned allocs_;   // Number of allocations (resizes)

      // Makes sure the subscript or position is valid.
      // Aborts the program if it's invalid.
    void check_bounds(unsigned index) const;
    
      // Grows the array when necessary. (Twice as large as before.)
      // Sizes of the array: 0, 1, 2, 4, 8, 16, etc.
    void grow(void);
    
    // Other private methods...
    void copy_array(const int *source, const unsigned size, int *destination);
    void reverse_copy_array(const int *source, const unsigned size, int *destination);

    template<typename T> void swap(T& a, T& b);
};

} // namespace CS170

#endif // VECTOR_H

