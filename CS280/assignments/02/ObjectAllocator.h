//---------------------------------------------------------------------------
#ifndef OBJECTALLOCATOR_H
#define OBJECTALLOCATOR_H
//---------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4290 ) // suppress warning: C++ Exception Specification ignored
#endif

#include <string>

// If the client doesn't specify these:
const int DEFAULT_OBJECTS_PER_PAGE = 128;
const int DEFAULT_MAX_PAGES = 64;

class OAException
{
  public:
    enum OA_EXCEPTION {E_NO_MEMORY, E_NO_PAGES, E_BAD_BOUNDARY, E_BAD_ADDRESS, E_MULTIPLE_FREE};
    OAException(int ErrCode, const std::string& Message) : error_code_(ErrCode), message_(Message) {};

    virtual ~OAException() {
    }

    virtual int code(void) const { 
      return error_code_; 
    }

		virtual const char *what(void) const {
      return message_.c_str();
    }
  private:  
    int error_code_;
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

class ObjectAllocator
{
  private:
    OAConfig Config_;            // configuration parameters
    unsigned ObjectSize_;        // size of each object
    unsigned PageSize_;          // size of a page: ObjectsPerPage_ * ObjectSize_ + sizeof(void*)
    unsigned NumPages_;          // number of pages allocated
    unsigned MostObjects_;       // most objects in use by client at one time
    unsigned ObjectsInUse_;      // number of objects currently in use

  public:
      // Creates the ObjectManager per the specified values
    ObjectAllocator(unsigned ObjectSize, const OAConfig& config);

      // Destroys the ObjectManager
    ~ObjectAllocator();

      // Take an object from the free list and give it to the client (simulates new)
      // Throws an exception if the object can't be allocated. (Memory allocation problem)
    void *Allocate() throw(OAException);

      // Returns an object to the free list for the client (simulates delete)
      // Throws an exception if the the object can't be freed. (Invalid object)
    void Free(void *Object) throw(OAException);

      // Testing/Debugging/Statistic methods
    void SetDebugState(bool State);       // true=enable, false=disable
};

#endif
