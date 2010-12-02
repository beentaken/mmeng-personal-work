// Marcus Meng
// CS180
// Assignment 5
// December 01, 2010

#include "MemoryManager.h"

MemoryManager::chunk_type::chunk_type(byte* start, unsigned int bytes)
:start_address(start), size(bytes), free(false)
{
}

MemoryManager::MemoryManager(int bytes)
:block_size_(bytes), block_(new byte[bytes]), chunks_()
{
	// Let's have a default block.
	chunks_.push_back(chunk_type(block_, bytes));
	(*chunks_.begin()).free = true;
}

MemoryManager::~MemoryManager()
{
	delete[] block_;
}

void* MemoryManager::allocate(int bytes)
{
	std::list<MemoryManager::chunk_type>::iterator it = find_empty_chunk(bytes);

	if (it == chunks_.end())
		return(NULL); // Couldn't find a place to stick it!
		
	chunks_.insert(it, chunk_type((*it).start_address, bytes));

	byte* start_pointer = (*it).start_address;

	(*it).size -= bytes;
	if ((*it).size == 0)
	{
		it = chunks_.erase(it);
	}
	else
	{
		(*it).start_address += bytes;
	}
	
	return(start_pointer);
}

void MemoryManager::deallocate(void* pointer)
{
	std::list<MemoryManager::chunk_type>::iterator it;
	
	for (it = chunks_.begin(); it != chunks_.end(); ++it)
	{
		if ((*it).start_address == pointer)
		{
			(*it).free = true;
			break;
		}
	}
	
	prune();
}

void MemoryManager::dump(std::ostream& os)
{
	std::list<MemoryManager::chunk_type>::iterator it;
	
	for (it = chunks_.begin(); it != chunks_.end(); ++it)
	{
		os << std::hex << std::noshowbase;
		// Make sure it doesn't think our memory block is a c_string.
		os << "start address: " << reinterpret_cast<void*>((*it).start_address) << std::endl;
		os << "  byte count: " << (*it).size << std::endl;
		os << "  allocated: " << (!((*it).free) ? "true" : "false") << std::endl;
	}
}

void MemoryManager::prune()
{
	std::list<MemoryManager::chunk_type>::iterator it1, it2;
	
	it1 = it2 = chunks_.begin();
	advance(it2, 1);
	
	while (it1 != chunks_.end() && it2 != chunks_.end())
	{
		while (it2 != chunks_.end() && (*it1).free && (*it2).free)
		{
			(*it1).size += (*it2).size;
			it2 = chunks_.erase(it2);
		}
		
		advance(it1, 1);
		advance(it2, 1);
	}
}

std::list<MemoryManager::chunk_type>::iterator MemoryManager::find_empty_chunk(unsigned int size)
{
	std::list<MemoryManager::chunk_type>::iterator it;

	for (it = chunks_.begin(); it != chunks_.end(); ++it)
	{
		if ((*it).free && (*it).size >= size)
			return it;
	}

	return(chunks_.end()); // Could not find memory chunk meeting specifications.
}

