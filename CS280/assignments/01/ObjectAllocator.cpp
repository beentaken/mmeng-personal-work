#include "ObjectAllocator.h"

ObjectAllocator::ObjectAllocator(unsigned ObjectSize, const OAConfig& config) throw(OAException)
{
}

ObjectAllocator::~ObjectAllocator() throw()
{
}

void* ObjectAllocator::Allocate() throw(OAException)
{
}

void ObjectAllocator::Free(void* Object) throw(OAException)
{
}

unsigned ObjectAllocator::DumpMemoryInUse(DMPCALLBACK fn) const
{
}



