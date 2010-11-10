/* Marcus Meng
	CS180
	Assignment 4
	November 10, 2010
*/

// Not debugging right now, turn off message spam.
#define NDEBUG

#include <windows.h>
#include <ctime>
#include <cstdlib>

#include <iostream>

#include "DotWindow.h"
#include "Compute.h"

class ThreadInfo
{
	HANDLE mutex_;
	Compute &computer_;
	
	public:
		ThreadInfo(HANDLE mutex, Compute &computer)
		:mutex_(mutex), computer_(computer)
		{
		}
		
		HANDLE getMutex()
		{
			return(mutex_);
		}
		
		Compute& getComputer()
		{
			return(computer_);
		}
};

void run_thread(ThreadInfo* data)
{
	DotWindow window("Dot Window");
	while (!window.IsClosed())
	{
		#ifndef NDEBUG
		std::cerr << "Thread " << GetCurrentThreadId() << ": Window not closed, stepping thread." << std::endl;
		#endif
		DWORD wait_result;
		wait_result = WaitForSingleObject(data->getMutex(), INFINITE); // Try to get the mutex.
				
		switch (wait_result)
		{
			// I can has ownership now.
			case WAIT_OBJECT_0:
			#ifndef NDEBUG
			std::cerr << "Thread " << GetCurrentThreadId() << ": Got my mutex lock." << std::endl;
			#endif
			double x, y;
			data->getComputer()(x, y);
			window.SetDotPosition(static_cast<int>(x), static_cast<int>(y));
						
			// Release the mutex.
			if (!ReleaseMutex(data->getMutex()))
			{
				// This is bad, somehow we couldn't release it.
				throw 1;
			}
			#ifndef NDEBUG
			std::cerr << "Thread " << GetCurrentThreadId() << ": Successfully released mutex." << std::endl;
			#endif
						
			break;
					
			case WAIT_ABANDONED:
			// ABORT!
			throw 1;
		}
	}
			
	#ifndef NDEBUG
	std::cerr << "Thread " << GetCurrentThreadId() << ": Window closed, GTFO tiemz." << std::endl;
	#endif
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	unsigned int num_threads = rand() % 10 + 1;
	Compute computer;
	
	HANDLE mutex = CreateMutex(NULL, false, NULL);
	
	ThreadInfo data(mutex, computer);
	
	DWORD threadID;
	HANDLE* threads = new HANDLE[num_threads];
	
	// Set up our threads.
	for (unsigned int i = 0; i < num_threads; ++i)
	{
		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) run_thread, &data, 0, &threadID);
	}
	
	// Let'em run until the user closes all the windows.
	WaitForMultipleObjects(num_threads, threads, true, INFINITE);
	
	// Cleanup.
	for (unsigned int i = 0; i < num_threads; ++i)
	{
		CloseHandle(threads[i]);
	}
	
	delete[] threads;
	
	CloseHandle(mutex);
	
	return(0);
}

