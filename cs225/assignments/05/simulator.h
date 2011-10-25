#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <queue>
#include "command.h"

//////////////////////////////////////////////////////////
/* explicit specialization for std::less<> which works with
 * pointers to TimedCommand.
 * It allowes to use STL containers of pointers to TimedCommand objects
 * without specifying comparison: 
 * Example (see simulator.h) instead of 
 *	std::priority_queue<TimedCommand*,std::vector<TimedCommand*>,PTCcompare> 
 *	where PTCcompare is a class that implements comparison
 *	bool operator() (const TimedCommand* lhs,const TimedCommand* rhs) ...
 *	we can just say 
 *	std::priority_queue<TimedCommand*> 
 */
namespace std {
	template <> 
		class less<TimedCommand*> {
			public:
				bool operator() 
					(const TimedCommand* lhs,const TimedCommand* rhs) const 
					{
						return *lhs < *rhs; 
					}
		};
}

/* main simulator class - runs an event-driven simulation */
class Simulator {
	public:
		void Start () {
			while ( !events.empty() ) {
				TimedCommand* ptc = events.top();
				events.pop();
				ptc->Execute();
				delete ptc;
			}
		}
		void AddEvent (TimedCommand* p_event) { 
			events.push(p_event); 
		}
	private:
		//std::priority_queue<TimedCommand*,std::vector<TimedCommand*>,PTCcompare> events;
		std::priority_queue<TimedCommand*> events;
};

#endif

