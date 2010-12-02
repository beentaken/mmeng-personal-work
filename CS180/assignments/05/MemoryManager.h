// Marcus Meng
// CS180
// Assignment 5
// December 01, 2010

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <iostream>
#include <list>

class MemoryManager
{
	public:
	
		typedef char byte;
	
		MemoryManager(int total_bytes);
		~MemoryManager();
		
		void* allocate(int bytes);
		void deallocate(void* pointer);
		void dump(std::ostream& os);
		
	private:
	
		// Simple struct to track individual chunks in our block of memory.
		struct chunk_type
		{
			chunk_type(byte* start, unsigned int bytes);
			byte* start_address;
			unsigned int size;
			bool free;
		};
		
		unsigned int block_size_; // The total size of the memory allocated in bytes.
		byte* block_; // The allocated memory.
		std::list<chunk_type> chunks_; // Contains starting address and length of each chunk.
		
		void prune(); // Prunes consecutive free memory chunks.
		std::list<chunk_type>::iterator find_empty_chunk(unsigned int size); // Finds the first empty chunk of given size.
};

#endif // MEMORY_MANAGER_H

