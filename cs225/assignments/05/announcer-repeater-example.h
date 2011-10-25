#ifndef RECIEVER_EXAMPLE_H
#define RECIEVER_EXAMPLE_H
#include <queue>
#include <string>
#include <iostream>
#include "command.h"
#include "simulator.h"

//////////////////////////////////////////////////////////
//this is the reciever class - it will be called when event occurs
class Announce {
	std::string msg;
	public:
	Announce(const std::string & _msg) : msg(_msg) {}
	void DoWork( double current_time );
};

//////////////////////////////////////////////////////////
//this is an event class that corresponds to Announce
//it has a pointer to an object and method
class AnnounceEvent : public TimedCommand {
	Announce* p_processor; //pointer to object
	void (Announce::*p_method)(double); //pointer to method

	public:
	AnnounceEvent(
			double when, //when to call
			Announce* _p_processor, //who to call
			void (Announce::*_p_method)(double)) //which method
		: p_processor(_p_processor), p_method(_p_method)
	{ SetWhen(when); }

	virtual void Execute() { (p_processor->*p_method)( When() ); }
};

// implementation of the method which is called through the event
void Announce::DoWork( double current_time ) {
	std::cout << "Announce: " << msg << " current time is " 
		<< current_time << ")\n";
}

//////////////////////////////////////////////////////////
//this is the reciever class - it will be called when event occurs
class Repeater {
	Simulator* psim;
	std::string msg;
	public:
	Repeater(Simulator* _psim, const std::string& _msg) :
		psim(_psim), msg(_msg) {}
	void ContinueRepeating( double,double,int );
};

//////////////////////////////////////////////////////////
//this is an event class that corresponds to Announce
//it has a pointer to an object and method
class RepeatingEvent : public TimedCommand {
	Repeater* p_processor;  //pointer to object
	void (Repeater::*p_method)(double,double,int); //pointer to method
	int how_many_times;  //argument
	double wait_period;  //argument
	public:
	RepeatingEvent(
			double when, //when to call
			Repeater* _p_processor, //who to call
			void (Repeater::*_p_method)(double,double,int), //which method
			int _how_many_times=1,  //what argument to use
			double _wait_period=1.0 //what argument to use
			)
		: p_processor(_p_processor), p_method(_p_method),
		how_many_times(_how_many_times), wait_period(_wait_period)
	{ 
		SetWhen(when);
	}
	virtual void Execute() {
		(p_processor->*p_method)(  When(), wait_period, --how_many_times );
	}
};

// implementation of the method which is called through the event
void Repeater::ContinueRepeating( 
		double current_time, 
		double interval, 
		int how_many_times_left ) 
{
	std::cout << "Repeater: " << msg << " (left " << how_many_times_left
		<< " current time is " << current_time << ")\n";

	// slightly non-trivial logic - this event may cause another event
	if (how_many_times_left>0) {
		std::cout << "Above message will be repeated at " 
			<< current_time+interval << std::endl;

		psim->AddEvent(
				new RepeatingEvent(
					current_time+interval, //scheduled time
					this,                  //object to call
					&Repeater::ContinueRepeating, //mthod to call
					how_many_times_left, //argument
					interval)            //argument
				);
	} else {
		std::cout << "This is the last message" << std::endl;
	}
}

#endif
