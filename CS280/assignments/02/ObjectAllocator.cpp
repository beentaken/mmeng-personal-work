#include "ObjectAllocator.h"

ObjectAllocator::ObjectAllocator(unsigned ObjectSize, const OAConfig& config) : Config_(config)
{
    // Initialize everything
  MostObjects_ = 0;
  NumPages_ = 0;
  ObjectsInUse_ = 0;
  ObjectSize_ = ObjectSize;
}

ObjectAllocator::~ObjectAllocator()
{
}

void *ObjectAllocator::Allocate(void) throw(OAException)
{
	if (!Config_.UseCPPMemManager_)
	{
		if ( (Config_.MaxPages_) && ObjectsInUse_>= Config_.MaxPages_ * Config_.ObjectsPerPage_)
			throw OAException(OAException::E_NO_PAGES, "AllocateObject: The maximum number of pages has been allocated.");
	}

  ObjectsInUse_++;
  if (ObjectsInUse_ > MostObjects_)
    MostObjects_ = ObjectsInUse_;

  return new char[ObjectSize_];
}

void ObjectAllocator::Free(void *anObject) throw(OAException)
{
  if (ObjectsInUse_ == 0)
    throw OAException(OAException::E_MULTIPLE_FREE, "FreeObject: Too many objects freed.");

  ObjectsInUse_--;
  delete [] reinterpret_cast<char *>(anObject);
}
