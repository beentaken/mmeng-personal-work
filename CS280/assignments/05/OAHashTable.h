/******************************************************************************/
/*!
\file   OAHashTable.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #5
\date   2010-03-31
\brief
  This is the header and prototypes for a simple hash table.

  The table supports user-passed hash functions that take a key and tablesize,
  and can use linear probing or double hasing to resolve collisions.
*/
/******************************************************************************/
//---------------------------------------------------------------------------
#ifndef OAHASHTABLE_H
#define OAHASHTABLE_H
//---------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma warning(disable: 4290 ) // Suppress warning: C++ Exception Specification ignored
#endif

#include <string>
#include "Support.h"

// client-provided hash function: takes a key and table size,
// returns an index in the table.
typedef unsigned (*HASHFUNC)(const char *, unsigned);

// Max length of our "string" keys
const unsigned MAX_KEYLEN = 10;

class OAHashTableException
{
  private:  
    int error_code_;
    std::string message_;

  public:
    OAHashTableException(int ErrCode, const std::string& Message) :
        error_code_(ErrCode), message_(Message) {};

    virtual ~OAHashTableException() {
    }

    virtual int code(void) const { 
      return error_code_; 
    }

    virtual const char *what(void) const {
      return message_.c_str();
    }
    enum OAHASHTABLE_EXCEPTION {E_ITEM_NOT_FOUND, E_DUPLICATE, E_NO_MEMORY};
};


enum OAHTDeletionPolicy {MARK, PACK};

// OAHashTable statistical info
struct OAHTStats
{
  OAHTStats(void) : Count_(0), TableSize_(0), Probes_(0), Expansions_(0),
                    PrimaryHashFunc_(0), SecondaryHashFunc_(0) {};
  unsigned Count_;             // Number of elements in the table
  unsigned TableSize_;         // Size of the table (total slots)
  unsigned Probes_;            // Number of probes performed
  unsigned Expansions_;        // Number of times the table grew
  HASHFUNC PrimaryHashFunc_;   // Pointer to primary hash function
  HASHFUNC SecondaryHashFunc_; // Pointer to secondary hash function
};

template <typename T>
class OAHashTable
{
  public:

    typedef void (*FREEPROC)(T); // client-provided free proc (we own the data)

      // Configuration values for the table
    struct OAHTConfig
    {
      OAHTConfig(unsigned InitialTableSize, 
                 HASHFUNC PrimaryHashFunc, 
                 HASHFUNC SecondaryHashFunc = 0,
                 double MaxLoadFactor = 0.5,
                 double GrowthFactor = 2.0, 
                 OAHTDeletionPolicy Policy = PACK,
                 FREEPROC FreeProc = 0) :

        InitialTableSize_(InitialTableSize), PrimaryHashFunc_(PrimaryHashFunc), 
        SecondaryHashFunc_(SecondaryHashFunc), MaxLoadFactor_(MaxLoadFactor), 
        GrowthFactor_(GrowthFactor), DeletionPolicy_(Policy),
        FreeProc_(FreeProc) {}

      unsigned InitialTableSize_;
      HASHFUNC PrimaryHashFunc_; 
      HASHFUNC SecondaryHashFunc_;
      double MaxLoadFactor_;
      double GrowthFactor_;
      OAHTDeletionPolicy DeletionPolicy_;
      FREEPROC FreeProc_;
    };
      
      // Slots that will hold the key/data pairs
    struct OAHTSlot
    {
      char Key[MAX_KEYLEN]; // Key is a string
      T Data;               // Client data is external
      enum OAHTSlot_State {OCCUPIED, UNOCCUPIED, DELETED};
      OAHTSlot_State State;
    };

    OAHashTable(const OAHTConfig& Config);
    ~OAHashTable();

      // Insert a key/data pair into table. Throws an exception if the
      // insertion is unsuccessful.
    void insert(const char *Key, const T& Data) throw(OAHashTableException);

      // Delete an item by key. Throws an exception if the key doesn't exist.
      // Compacts the table by moving key/data pairs, if necessary
    void remove(const char *Key) throw(OAHashTableException);

      // Find and return data by key (throws exception if not found)
    const T& find(const char *Key) const throw(OAHashTableException);

      // Removes all items from the table (Doesn't deallocate table)
    void clear(void);

      // Allow the client to peer into the data
    OAHTStats GetStats(void) const;
    const OAHTSlot *GetTable(void) const;

  private:
      // Initialize the table after an allocation
    void InitTable(void);

      // Expands the table when the load factor reaches a certain point
      // (greater than MaxLoadFactor) Grows the table by GrowthFactor,
      // making sure the new size is prime by calling GetClosestPrime
    void GrowTable(void) throw(OAHashTableException);

      // Workhorse method to locate an item (if it exists)
      // Returns the index of the item in the table
      // Sets Slot to point to the slot in the table where it belongs 
      // Returns -1 if it's not in the table
    int IndexOf(const char *Key, OAHTSlot* &Slot) const;
    
    // Other private fields and methods...
    OAHTConfig myConfig;
    OAHTSlot* myTable;
    mutable OAHTStats myStats;

    void myRemove(OAHTSlot &to_remove) throw(OAHashTableException);
    int myIndex(const unsigned &hash, const unsigned &stride, const unsigned& index) const;

    unsigned mySecondaryHash(const char* key) const;
    unsigned myPrimaryHash(const char* key) const;
};

#include "OAHashTable.cpp"

#endif

