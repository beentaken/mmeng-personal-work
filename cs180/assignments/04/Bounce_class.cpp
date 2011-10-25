/* Marcus Meng
	CS180
	Assignment 04
	November 10, 2010
	*/

#include <windows.h>
#include <list>
#include <string>
#include <functional>
#include <iostream>
	
#include "Compute.h"
#include "DotWindow.h"

class WindowThread
{
	private:
		DotWindow window_;
		HANDLE thread_;
		HANDLE mutex_;
		Compute& computer_;
		DWORD threadID;
	public:
	
		WindowThread(std::string title, HANDLE mutex, Compute &computer)
		:window_(title.c_str()), thread_(NULL), mutex_(mutex), computer_(computer)
		{
		}

		~WindowThread()
		{
			CloseHandle(thread_);
			#ifndef NDEBUG
			std::cerr <<  "Thread " << GetCurrentThreadId() << ": Thread closed." << std::endl;
			#endif
		}
		
		WindowThread& operator=(const WindowThread &rhs)
		{
			window_ = rhs.window_;
			thread_ = rhs.thread_;
			mutex_ = rhs.mutex_;
			computer_ = rhs.computer_;
			threadID = rhs.threadID;
			
			return(*this);
		}
		
		void start()
		{
			if (thread_ != NULL)
			{
				// We're not supposed to have a thread yet!
				throw 1;
			}
			thread_ = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) &WindowThread::step, this, 0, &threadID);
			
			if (thread_ == NULL)
			{
				// OSHI-
				throw 1;
			}
			#ifndef NDEBUG
			std::cerr << "Thread " << GetCurrentThreadId() << ": Thread created." << std::endl;
			#endif
		}
		
		bool isClosed()
		{
			#ifndef NDEBUG
			std::cerr << "Thread " << GetCurrentThreadId() << ": Checking if window is closed." << std::endl;
			#endif
			return(window_.IsClosed());
		}
		
		static DWORD WINAPI step(WindowThread* current)
		{
			while (!current->window_.IsClosed())
			{
				#ifndef NDEBUG
				std::cerr << "Thread " << GetCurrentThreadId() << ": Window not closed, stepping thread." << std::endl;
				#endif
				DWORD wait_result;
				wait_result = WaitForSingleObject(current->mutex_, INFINITE); // Try to get the mutex.
				
				switch (wait_result)
				{
					// I can has ownership now.
					case WAIT_OBJECT_0:
						#ifndef NDEBUG
						std::cerr << "Thread " << GetCurrentThreadId() << ": Got my mutex lock." << std::endl;
						#endif
						double x, y;
						current->computer_(x, y);
						current->window_.SetDotPosition(static_cast<int>(x), static_cast<int>(y));
						
						// Release the mutex.
						if (!ReleaseMutex(current->mutex_))
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
			
			return(true);
		}
};

int main()
{
	const unsigned int num_threads(5);
	std::list<WindowThread> threads;
	Compute position_computer;
	
	HANDLE mutex = CreateMutex(NULL, FALSE, NULL);
	
	if (mutex == NULL)
	{
		// BAD!
		return(1);
	}

	// Set up threads.
	for (int i(0); i < num_threads; ++i)
	{
		threads.push_back(WindowThread("Test", mutex, position_computer));
	}
	
	// Start threads.
	std::list<WindowThread>::iterator it;
	
	for (it = threads.begin(); it != threads.end(); ++it)
	{
		it->start();
	}
	
	// Threads should run on their own. They should stop running when isClosed() is true.
	// If it closes, we remove the thread from the list.
	while (!threads.empty())
	{
		#ifndef NDEBUG
		std::cerr << "Main: Thread list isn't empty, " << threads.size() << " items left." << std::endl;
		#endif
		std::list<WindowThread>::iterator it;
		
		threads.remove_if(std::mem_fun_ref(&WindowThread::isClosed));
		
		Sleep(50);
	}
	#ifndef NDEBUG
	std::cerr << "Main: Thread list empty, time to clean up." << std::endl;
	#endif
	
	// Clean up our mutex.
	CloseHandle(mutex);

	return(0);
}
