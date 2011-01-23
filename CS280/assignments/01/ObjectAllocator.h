//---------------------------------------------------------------------------
#ifndef OBJECTALLOCATORH
#define OBJECTALLOCATORH
//---------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma warning( disable : 4290 ) // suppress warning: C++ Exception Specification ignored
#endif

#include <string>

// If the client doesn't specify these:
static const int DEFAULT_OBJECTS_PER_PAGE = 4;  
static const int DEFAULT_MAX_PAGES = 3;

class OAException
{
  public:
      // Possible exception codes
    enum OA_EXCEPTION 
    {
      E_NO_MEMORY,      // out of physical memory (operator new fails)
      E_NO_PAGES,       // out of logical memory (max pages has been reached)
      E_BAD_ADDRESS,    // block address is not on a page
      E_BAD_BOUNDARY,   // block address is on a page, but not on any block-boundary
      E_MULTIPLE_FREE,  // block has already been freed
      E_CORRUPTED_BLOCK // block has been corrupted (pad bytes have been overwritten)
    };

    OAException(OA_EXCEPTION ErrCode, const std::string& Message) : error_code_(ErrCode), message_(Message) {};

    virtual ~OAException() {
    }

    OA_EXCEPTION code(void) const { 
      return error_code_; 
    }

    virtual const char *what(void) const {
      return message_.c_str();
    }
  private:  
    OA_EXCEPTION error_code_;
    std::string message_;
};

// ObjectAllocator configuration parameters
struct OAConfig
{
  OAConfig(bool UseCPPMemManager = false, 
           unsigned ObjectsPerPage = DEFAULT_OBJECTS_PER_PAGE, 
           unsigned MaxPages = DEFAULT_MAX_PAGES, 
           bool DebugOn = false, 
           unsigned PadBytes = 0,
           unsigned HeaderBlocks = 0,
           unsigned Alignment = 0) : UseCPPMemManager_(UseCPPMemManager), 
                                     ObjectsPerPage_(ObjectsPerPage), 
                                     MaxPages_(MaxPages), 
                                     DebugOn_(DebugOn), 
                                     PadBytes_(PadBytes),
                                     HeaderBlocks_(HeaderBlocks),
                                     Alignment_(Alignment)
  {
    LeftAlignSize_ = 0;
    InterAlignSize_ = 0;
  }

  bool UseCPPMemManager_;   // by-pass the functionality of the OA and use new/delete
  unsigned ObjectsPerPage_; // number of objects on each page
  unsigned MaxPages_;       // maximum number of pages the OA can allocate (0=unlimited)
  bool DebugOn_;            // enable/disable debugging code (signatures, checks, etc.)
  unsigned PadBytes_;       // size of the left/right padding for each block
  unsigned HeaderBlocks_;   // size of the header for each block (0=no headers)
  unsigned Alignment_;      // address alignment of each block

  unsigned LeftAlignSize_;  // number of alignment bytes required to align first block
  unsigned InterAlignSize_; // number of alignment bytes required between remaining blocks
};

// ObjectAllocator statistical info
struct OAStats
{
  OAStats(void) : ObjectSize_(0), FreeObjects_(0), ObjectsInUse_(0), PagesInUse_(0),
                  PageSize_(0), MostObjects_(0), Allocations_(0), Deallocations_(0) {};

  unsigned ObjectSize_;    // size of each object
  unsigned FreeObjects_;   // number of objects on the free list
  unsigned ObjectsInUse_;  // number of objects in use by client
  unsigned PagesInUse_;    // number of pages allocated
  unsigned PageSize_;      // size of a page: ObjectsPerPage_ * ObjectSize_ + sizeof(void*)
  unsigned MostObjects_;   // most objects in use by client at one time
  unsigned Allocations_;   // total requests to allocate memory
  unsigned Deallocations_; // total requests to free memory
};

// This allows us to easily treat raw objects as nodes in a linked list
struct GenericObject
{
  GenericObject *Next;
};

// This memory manager class 
class ObjectAllocator
{
  public:
    typedef void (*DUMPCALLBACK)(const void *, unsigned int);
    typedef void (*VALIDATECALLBACK)(const void *, unsigned int);

      // Predefined values for memory signatures
    static const unsigned char UNALLOCATED_PATTERN = 0xaa;
    static const unsigned char ALLOCATED_PATTERN = 0xbb;
    static const unsigned char FREED_PATTERN = 0xcc;
    static const unsigned char PAD_PATTERN = 0xdd;
    static const unsigned char ALIGN_PATTERN = 0xee;

      // Creates the ObjectManager per the specified values
      // Throws an exception if the construction fails. (Memory allocation problem)
    ObjectAllocator(unsigned ObjectSize, const OAConfig& config) throw(OAException);

      // Destroys the ObjectManager (never throws)
    ~ObjectAllocator() throw();

      // Take an object from the free list and give it to the client (simulates new)
      // Throws an exception if the object can't be allocated. (Memory allocation problem)
    void *Allocate() throw(OAException);

      // Returns an object to the free list for the client (simulates delete)
      // Throws an exception if the the object can't be freed. (Invalid object)
    void Free(void *Object) throw(OAException);

      // Calls the callback fn for each block still in use
    unsigned DumpMemoryInUse(DUMPCALLBACK fn) const;

      // Calls the callback fn for each block that is potentially corrupted
    unsigned ValidatePages(VALIDATECALLBACK fn) const;

      // Frees all empty pages
    unsigned FreeEmptyPages(void);

      // Returns true if FreeEmptyPages and alignments are implemented
    static bool ImplementedExtraCredit(void);

      // Testing/Debugging/Statistic methods
    void SetDebugState(bool State);       // true=enable, false=disable
    const void *GetFreeList(void) const;  // returns a pointer to the internal free list
    const void *GetPageList(void) const;  // returns a pointer to the internal page list
    OAConfig GetConfig(void) const;       // returns the configuration parameters
    OAStats GetStats(void) const;         // returns the statistics for the allocator

  private:
    OAConfig Config_;            // configuration parameters
    OAStats OAStats_;            // accumulating statistics

      // Make private to prevent copy construction and assignment
    ObjectAllocator(const ObjectAllocator &oa);
    ObjectAllocator &operator=(const ObjectAllocator &oa);
    
    // Other private fields and methods...
};

#endif
