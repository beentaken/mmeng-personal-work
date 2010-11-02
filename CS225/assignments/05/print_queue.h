/*****************************************************************************/
/*!
\file   print_queue.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 5
\date   17 July, 2010
\brief
	This file contains the prototypes for a simple callback-based print
	queue that runs inside a simulator object.
*/
/*****************************************************************************/

#ifndef PRINT_QUEUE_H
#define PRINT_QUEUE_H
#include <queue>
#include <map>
#include <iostream>
#include "command.h"
#include "printjob.h"
#include "simulator.h"

/* this is a comparison for PrintQueue::jobs_in_queue
 * jobs in the above queue should have time associated with them, 
 * since the original PrintJob doesn't have time, we add it by creating 
 * std::pair<PrintJob,double>
 * where the first is job, second is time (of arrival)
 * these pairs have to be ordered by priority first then by time
 * since there is no standard std::less for pairs, we have to define our own
 * Note: working with pairs:
 * - to declare use 
 *   		std::pair<type1,type2> p;
 * - to create a pair object 
 *   		p = std::make_pair<type1,type2>(obj1,obj2)
 * - to access 
 *   		type1 obj1 = p.first;
 *   		type2 obj1 = p.second;
 */
namespace std {
	template <>
		class less<std::pair<PrintJob,double> > {
			public:
				bool operator() (
						const std::pair<PrintJob,double>& p1,
						const std::pair<PrintJob,double>& p2) const
				{
					//since queue puts the biggest on top, we have to reverse 
					//comparison for time: 
					//so for a PrintJob to be closer to top (>) it has to
					//   have higher priority or same priority and smaller time
					//or for a PrintJob to be further from top (<) it has to
					//   have lower priority or same priority and bigger time
					return 	(p1.first<p2.first) ||  //priority is more important than time
						(!(p2.first<p1.first) && p1.second>p2.second);//if same priority,
												//then compare time 
				}
		};
}

/*
 * print queue logic,
 * Basics: print queue sits between the clients and printers. Clients submit 
 * theirs print jobs to the queue which then sends them to an available 
 * printer. If no printer is available when jobs arrives, the job is placed
 * to a queue, which is ordered by job priority. When the next printer is done
 * it is assigned the first job in the queue.
 * 3 main logic components:
 * 1) priority queue (ordered by job priority and arrival time)
 * 2) when printer finishes a job, check if there are any jobs in the queue,
 * assign the top most to the printer
 * 3) when job arrives, check if printer is available, assign to it. If 
 * no printer is available, put into the queue.
 */
class PrintQueue {
	Simulator* psim; //where events are added
	int num_available_printers; //instead of walking through all printers, just 
	//check if this number is >0

	public:
	PrintQueue(Simulator* _psim);
	void RegisterPrinter(int ID, double speed);
	void JobFinished( double current_time, int printerID, PrintJob job );
	void NewJobArrived( double current_time, PrintJob job );

	private:
	typedef std::map<int,std::pair<bool,double> > ID2pair;
	//all printers in the system are stored here
	//map: ID -> (available,speed) -- see typedef above
	ID2pair printer_status;
	//print job queue
	std::priority_queue< std::pair<PrintJob,double> > jobs_in_queue;
};

/* "printer just finished a job" event
 * has information about completed job and printer
 */
class EventJobFinished : public TimedCommand
{
	int printer_id;
	PrintJob job;
	PrintQueue *p_print_queue;
	public:
		EventJobFinished(double _when, int _printer_id, const PrintJob &_job, PrintQueue *_p_print_queue);
		virtual void Execute(void);
};

/* new job just arrived event, has information about the job*/
class EventNewJobArrived : public TimedCommand
{
	PrintJob job;
	PrintQueue* p_print_queue;
	void (PrintQueue::*p_method)(double,PrintJob);
	public:
	EventNewJobArrived(
			double _when, 
			const PrintJob& _job,
			PrintQueue* _p_print_queue, 
			void (PrintQueue::*_p_method)(double,PrintJob)
			);
	virtual void Execute();
};

#endif

