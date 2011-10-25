/******************************************************************************/
/*!
\file   ObjectAllocator.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS280
\par    Assignment #1
\date   2010-01-27
\brief  
  This is the implementation file for a fixed-blocksize allocator class.
  
*/
/******************************************************************************/

#include "ObjectAllocator.h"

// Anon namespace helpers! Because typing out reinterpret casts every time really, really sucks.
namespace
{
	/*! \brief Helper function to cast pointers into GenericObject pointers.
	 *
	 * \param toCast
	 *   The pointer to cast into a GenericObject*.
	 *
	 * \return
	 *   A GenericObject*.
	 */
	inline GenericObject* GenObjCast(void* toCast)
	{
		return(reinterpret_cast<GenericObject*>(toCast));
	}
}

/*!\brief Constructor for an ObjectAllocator.
 *
 * Note that the default constructors and copy constructors are deliberately
 * hidden --- the arguments for this function MUST be provided for this class
 * to function properly.
 *
 * \param ObjectSize
 * 	The size in bytes of the objects to be allocated.
 *
 * \param config
 * 	An OAConfig containing specific details on what needs to be run
 * 	in this class.
 */
ObjectAllocator::ObjectAllocator(unsigned ObjectSize, const OAConfig& config) throw(OAException)
:Config_(config), Stats_(), page_list_(NULL), free_list_(NULL)
{
	Stats_.ObjectSize_ = ObjectSize;
	Stats_.PageSize_ = myGetPageSize();

	Config_.LeftAlignSize_ = Config_.Alignment_ % (static_cast<unsigned>(sizeof(void*)) + Config_.HeaderBlocks_ + Config_.PadBytes_);
	Config_.InterAlignSize_ = Config_.Alignment_ % (Stats_.ObjectSize_ + Config_.PadBytes_ * 2 + Config_.HeaderBlocks_);

	page_list_ = static_cast<char*>(myAllocatePage());
}

ObjectAllocator::~ObjectAllocator() throw()
{
	myDestructor(GenObjCast(page_list_));
}

/*!\brief Allocates one fixed-size object for the user from a page that the
 * class is currently holding.
 *
 * \exception Throws an OAException if the computer is out of physical memory
 * or unable to allocate a new page, either due to lack of physical memory or
 * due to a logical memory constraint.
 *
 * \return A pointer to the newly allocated object.
 */
void* ObjectAllocator::Allocate() throw(OAException)
{
	GenericObject* to_return;
	if (Config_.UseCPPMemManager_)
	{
		to_return = GenObjCast(new char[Stats_.ObjectSize_]);
	}
	else
	{
		// If we're out of blocks in our current set of pages...
		if (free_list_ == NULL)
		{
			GenObjCast(page_list_)->Next = GenObjCast(myAllocatePage());
		}

		// Now that we have an open free list (if the above failed, an exception hit, so...)
		to_return = free_list_;
		free_list_ = free_list_->Next;

		if (Config_.DebugOn_)
		{
			mySetAllocated(reinterpret_cast<char*>(to_return));
			mySetHeaderBlockOn(reinterpret_cast<char*>(to_return));
		}
	}

	// Administrative trivia 2: Electric Boogaloo.
	++Stats_.Allocations_;
	++Stats_.ObjectsInUse_;
	--Stats_.FreeObjects_;

	if (Stats_.ObjectsInUse_ > Stats_.MostObjects_)
		Stats_.MostObjects_ = Stats_.ObjectsInUse_;

	return(to_return);
}

/*!\brief Frees a previously-allocated object in one of the pages that the
 * class holds.
 *
 * \param Object
 * 	The memory address of the object to be freed.
 *
 * \exception This function does some checking if the class is set to debug
 * mode. It can throw an OAException under the following conditions:
 * - Multiple Frees
 * - Bad Boundary
 * - Invalid Address
 */
void ObjectAllocator::Free(void* Object) throw(OAException)
{
	if (Config_.UseCPPMemManager_)
	{
		delete static_cast<GenericObject*>(Object);
	}
	else
	{
		// These will throw exceptions if bad things happen.
		if (Config_.DebugOn_)
		{
			myCheckAddressBoundary(Object);
			myCheckDoubleFree(Object, free_list_);

			mySetFreed(static_cast<char*>(Object));
			mySetHeaderBlockOff(static_cast<char*>(Object));
		}

		// Alright, toss it right back on the free list.
		GenObjCast(Object)->Next = free_list_;
		free_list_ = GenObjCast(Object);
	}

	// Finish up the tracking and administration.
	++Stats_.Deallocations_;
	++Stats_.FreeObjects_;
	--Stats_.ObjectsInUse_;
}

/*!\brief Provides a dump of all the memory addresses of the blocks that are
 * currently in use.
 *
 * \param fn
 * 	A function pointer to a function to run on all in-use memory addresses.
 *
 * \return The number of objects currently in use.
 */
unsigned ObjectAllocator::DumpMemoryInUse(DUMPCALLBACK fn) const
{
	// TODO: Stub!
	return(Stats_.ObjectsInUse_);
}

/*!\brief Attempts to detect memory corruption in the pages allocated.
 *
 * Does so using canary values bordering all allocated memory addresses.
 *
 * Overwritten canaries would imply over or underflows.
 *
 * \param fn
 * 	A function to run on all potentially corrupted addresses.
 *
 * \return The number of potentially corrupted pages found.
 */
unsigned ObjectAllocator::ValidatePages(VALIDATECALLBACK fn) const
{
	unsigned count = 0;
/*	for(char* temp_list = page_list_; temp_list != NULL; GenObjCast(temp_list) = GenObjCast(temp_list)->Next)
	{
		for (int i = 0; i < Config_.ObjectsPerPage_; ++i)
		{
			try
			{
				myCheckPadBytes(temp_list + myFindBlockOffset(i));
			}
			catch (OAException &)
			{
				count++;
				fn(temp_list + myFindBlockOffset(i));
			}
		}
	}*/
	return(count);
}

/*!\brief Frees and removes pages with no allocated data inside them.
 *
 * \return The number of pages freed.
 */
unsigned ObjectAllocator::FreeEmptyPages()
{
	// TODO: Stub!
	// Returns number of pages freed.
	return(0U);
}

/*!\brief Tells whether or not to test against extra credit.
 *
 * \return True if extra credit is implemented, false otherwise.
 */
bool ObjectAllocator::ImplementedExtraCredit()
{
	// TODO: Sorta stub. Return true if extra credit is done.
	return(false);
}

/*!\brief Sets the debug state for the allocator.
 *
 * \param State
 * 	This should be true if you want debugging, false otherwise.
 */
void ObjectAllocator::SetDebugState(bool State)
{
	Config_.DebugOn_ = State;
}

/*!\brief Returns a pointer to the freelist.
 *
 * For debug purposes only.
 *
 * \return a constant pointer to the freelist.
 */
const void* ObjectAllocator::GetFreeList() const
{
	return(free_list_);
}

/*!\brief Returns a pointer to the page list.
 *
 * For debug purposes only.
 *
 * \return a constant pointer to the page list.
 */
const void* ObjectAllocator::GetPageList() const
{
	return(page_list_);
}

/*!\brief Returns the current configuration of the class.
 *
 * \return an OAConfig containing the current configuration.
 */
OAConfig ObjectAllocator::GetConfig() const
{
	return(Config_);
}

/*!\brief Obtains some stats about the allocator's usage.
 *
 * \return An OAStats containing information about the allocations.
 */
OAStats ObjectAllocator::GetStats() const
{
	return(Stats_);
}


/**************************************************
 * Private functions.
 */

/*!\brief Obtains the size of each page.
 *
 * \return The size of a page.
 */
inline unsigned ObjectAllocator::myGetPageSize() const
{
	// Weird addition at the end because last block doesn't have align, etc for next block.
	return(myGetInitialChunkSize() + (Config_.ObjectsPerPage_ - 1) * myGetDataChunkSize()
			+ Stats_.ObjectSize_ + Config_.PadBytes_);
}

/*!\brief Allocates a new page.
 *
 * Used to link into the new page list when the current pages
 * are out of allocatable memory.
 *
 * \exception Can throw OAExceptions when there is no logical or physical
 * memory available for usage.
 *
 * \return A pointer to the newly allocated page.
 */
void* ObjectAllocator::myAllocatePage() throw(OAException)
{
	if (Stats_.PagesInUse_ == Config_.MaxPages_)
	{
		throw OAException(OAException::E_NO_PAGES, "Cannot allocate new page: page limit reached.");
	}

	char* new_page;
	try
	{
		new_page = new char[myGetPageSize()];
	}
	catch(std::bad_alloc &)
	{
		throw OAException(OAException::E_NO_MEMORY, "Cannot allocate new page: No system memory available.");
	}

	if (Config_.DebugOn_)
	{
		mySetUnallocated(new_page);
	}

	// Initial Next page pointer is always NULL.
	GenObjCast(new_page)->Next = NULL;

	// Link the free list backwards.
	// First node doesn't have to be linked, so start from 1, not 0.
	for (unsigned i = 1; i < Config_.ObjectsPerPage_; ++i)
	{
		GenObjCast(&new_page[myFindBlockOffset(i)]) ->Next = GenObjCast(&new_page[myFindBlockOffset(i-1)]);
		
		if (Config_.DebugOn_)
		{
			mySetPadBytes(new_page + myFindBlockOffset(i));
			mySetAlign(new_page + myFindBlockOffset(i));
			mySetHeaderBlockOff(new_page + myFindBlockOffset(i));
		}
	}

	// Handle end cases for the free list.
	GenObjCast(&new_page[myFindBlockOffset(0)])->Next = free_list_;
	free_list_ = GenObjCast(&new_page[myFindBlockOffset(Config_.ObjectsPerPage_ - 1)]);

	// And end cases for the various pads and stuff.
	// Note that the align is handled manually, since the first alignment is weird.
	if (Config_.DebugOn_)
	{
		mySetPadBytes(new_page + myFindBlockOffset(0));
		mySetHeaderBlockOff(new_page + myFindBlockOffset(0));

		myFillBytes(new_page - Config_.PadBytes_ - Config_.HeaderBlocks_ - Config_.LeftAlignSize_,
				new_page - Config_.PadBytes_ - Config_.HeaderBlocks_, ALIGN_PATTERN);
	}

	// Administrative trivia.
	++Stats_.PagesInUse_;
	Stats_.FreeObjects_ += Config_.ObjectsPerPage_;

	return(new_page);
}

/*!\brief Finds a value that can be added to the start of any page to find the
 * address of the block with the given index.
 * 
 * Use this instead of attempting to iterate through the blocks in a page
 * manually.
 *
 * \param index
 * 	The index of the block to obtain.
 *
 * \return The offset from the start of the page of the block requested.
 */
inline unsigned ObjectAllocator::myFindBlockOffset(unsigned index) const
{
	return(myGetInitialChunkSize() + index * myGetDataChunkSize());
}

/*!\brief Gets the size of the first pointer, align buffer, header, and pad
 * byte set. This is how much the following blocks will be offset by
 * relative to the start of the page.
 *
 * \return The amount the first block is offset by.
 */
inline unsigned ObjectAllocator::myGetInitialChunkSize() const
{
	return(static_cast<unsigned>(sizeof(void*)) + Config_.LeftAlignSize_ + Config_.HeaderBlocks_ + Config_.PadBytes_);
}

/*!\brief Gets the size of each block internally, including all alignment
 * buffers, header blocks, and pad bytes.
 *
 * \return The size of each block.
 */
inline unsigned ObjectAllocator::myGetDataChunkSize() const
{
	return(Stats_.ObjectSize_ + Config_.InterAlignSize_ + 2 * Config_.PadBytes_ + Config_.HeaderBlocks_);
}

/*!\brief Helper function to free all the allocated pages when
 * the object is destroyed.
 *
 * Functions recursively.
 *
 * \param page_to_destroy
 * 	The current page to consider deallocating.
 */
void ObjectAllocator::myDestructor(GenericObject* page_to_destroy)
{
	if (page_to_destroy != NULL)
	{
		myDestructor(page_to_destroy->Next);
		delete[] page_to_destroy;
	}
}

/*!\brief Helper function that locates which page a given address is on.
 *
 * \exception Throws an OAException if the given address is not located on any page.
 *
 * \param Object
 * 	The address to check.
 *
 * \param current_page
 * 	Iterator variable, tracks what page the function is currently checking.
 *
 * \return
 * 	A pointer to the page containing the object.
 */
void* ObjectAllocator::myFindPage(void* Object, GenericObject* current_page) const throw(OAException)
{
	if (current_page != NULL)
	{
		/*
		if (static_cast<char*>(Object) < reinterpret_cast<char*>(current_page) || 
			(static_cast<char*>(Object) >= (reinterpret_cast<char*>(current_page) + myGetPageSize())))*/
		for (unsigned i = 0; i < myGetPageSize(); ++i)
		{
			if (reinterpret_cast<char*>(current_page) + i == Object)
				return(current_page);
		}
		return(myFindPage(Object, current_page->Next));
	}

	throw OAException(OAException::E_BAD_ADDRESS, "Address does not exist on any pages.");

	// Technically probably won't ever get here, buuuut...
	return(NULL);
}

/*!\brief Checks whether a given address is correctly aligned to a provided boundary.
 *
 * \param Object
 * 	The address to check.
 *
 * \exception Throws an OAException if the object is not on one of the predefined
 * boundaries.
 */
void ObjectAllocator::myCheckAddressBoundary(void * Object) const throw(OAException)
{
	char* current_page = static_cast<char*>(myFindPage(Object, GenObjCast(page_list_)));

	if ((((static_cast<char*>(Object) - current_page) - myGetInitialChunkSize()) % myGetDataChunkSize()) != 0)
	{
		// Something bad happened, abort, abort!
		throw OAException(OAException::E_BAD_BOUNDARY, "Address not aligned to boundaries.");
	}
}

/*!\brief Checks whether the provided object has already been freed.
 *
 * \param Object
 * 	The memory address to check.
 *
 * \param current_node
 * 	An iterator variable to track which block the object is currently
 * 	being matched against.
 *
 * \exception
 * 	Throws an OAException if the object has already been freed.
 */
void ObjectAllocator::myCheckDoubleFree(void* Object, GenericObject* current_node) const throw(OAException)
{
	if (current_node != NULL)
	{
		if (current_node == Object)
			throw OAException(OAException::E_MULTIPLE_FREE, "Multiple frees detected.");
		myCheckDoubleFree(Object, current_node->Next);
	}
}

/*!\brief Helper function. Fills the given memory range with the given
 * character.
 *
 * \param range_start
 * 	The start of the range to fill.
 *
 * \param range_end
 * 	The end of the range to fill.
 *
 * \param fill
 * 	The character to fill the range with.
 */
void ObjectAllocator::myFillBytes(char* range_start, char* range_end, char fill)
{
	while (range_start != range_end)
	{
		*range_start = fill;
		++range_start;
	}
}

/*!\brief Sets the pad bytes around the given address to the pad pattern.
 *
 * \param address
 * 	The address to set the pad bytes around.
 */
void ObjectAllocator::mySetPadBytes(char* address)
{
	myFillBytes(address - Config_.PadBytes_, address, PAD_PATTERN);
	myFillBytes(address + Stats_.ObjectSize_, address + Stats_.ObjectSize_ + Config_.PadBytes_, PAD_PATTERN);
}

/*!\brief Sets the given page to Unallocated pattern.
 *
 * \param page
 * 	The page to blank out.
 */
void ObjectAllocator::mySetUnallocated(char* page)
{
	myFillBytes(page, page + myGetPageSize(), UNALLOCATED_PATTERN);
}

/*!\brief Sets the object at the given address to an allocated pattern.
 *
 * \param address
 * 	The address to set to allocated.
 */
void ObjectAllocator::mySetAllocated(char* address)
{
	myFillBytes(address, address + Stats_.ObjectSize_, ALLOCATED_PATTERN);
}

/*!\brief Sets the given address to a freed pattern.
 *
 * \param address
 * 	The address to set to the freed pattern.
 */
void ObjectAllocator::mySetFreed(char* address)
{
	myFillBytes(address, address + Stats_.ObjectSize_, FREED_PATTERN);
}

/*!\brief Sets the alignment bytes near an address to the specified alignment pattern.
 *
 * \param address
 * 	The address to specify the alignment bytes around.
 */
void ObjectAllocator::mySetAlign(char* address)
{
	myFillBytes(address + Config_.PadBytes_, address + Config_.PadBytes_ + Config_.InterAlignSize_, ALIGN_PATTERN);
}

/*!\brief Sets the header block to the 0 (deallocated) pattern.
 *
 * \param address
 * 	The address associated with the header block to change.
 */
void ObjectAllocator::mySetHeaderBlockOff(char* address)
{
	myFillBytes(address - Config_.PadBytes_ - Config_.HeaderBlocks_, address - Config_.PadBytes_, 0);
}

/*!\brief Sets the header block to the 1 (allocated) pattern.
 *
 * \param address
 * 	The address associated with the header block to change.
 */
void ObjectAllocator::mySetHeaderBlockOn(char* address)
{
	if (Config_.HeaderBlocks_ != 0)
		myFillBytes(address - Config_.PadBytes_ - 1, address - Config_.PadBytes_, 1);
}

/*!\brief Checks the pad bytes around the given address.
 *
 * \param address
 * 	The address around which to check.
 *
 * \exception Throws an OAException if the pad bytes have been tampered with.
 */
void ObjectAllocator::myCheckPadBytes(char* address) const throw(OAException)
{
	char* current;

	for (current = address - Config_.PadBytes_; current != address; ++current)
	{
		if ((*current) != PAD_PATTERN)
			throw OAException(OAException::E_CORRUPTED_BLOCK, "Corrupted block detected!");
	}
}

