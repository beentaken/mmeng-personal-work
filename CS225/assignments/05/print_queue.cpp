/*****************************************************************************/
/*!
\file   print_queue.cpp
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 5
\date   17 July, 2010
\brief
	This file contains the implementations for a basic print queue that
	runs in a simulator object.
*/
/*****************************************************************************/

#include "print_queue.h"

////////////////////////////////////////////////////////////
/* PrintQueue implementation */
////////////////////////////////////////////////////////////

/* \brief Constructor.
 *
 * \param _psim
 * 	The simulator to run the queue within.
 */ 
PrintQueue::PrintQueue(Simulator* _psim) : 
	psim(_psim),num_available_printers(0) 
{}

/* \brief Registers a printer inside the queue, making it available for usage.
 *
 * \param ID
 * 	The ID tag to give to the printer.
 *
 * \param speed
 * 	The speed of the printer.
 */
void PrintQueue::RegisterPrinter(int ID, double speed) {
	/* pair of (ID and a pair (available, speed) ) */
//	printer_status.insert( 
//			std::make_pair<int,std::pair<bool,double> >
//			         (ID,std::make_pair<bool,double>(true,speed) ) 
//			);
//next line is equivalent to the above insert
	printer_status[ ID ] = std::make_pair<bool,double>(true,speed);
	//printer is available by default
	++num_available_printers;
}

/* \brief A function that should be called when a job is finally sent to and
 * processed by the printer.
 *
 * \param current_time
 * 	The time that the job finished and called this function.
 *
 * \param printerID
 * 	The ID of the printer that completed the job.
 *
 * \param job
 * 	The job that has just been completed.
 */
void PrintQueue::JobFinished( double current_time, int printerID, PrintJob job)
{
	ID2pair::iterator it = printer_status.find( printerID );

	if ( it == printer_status.end() ) throw "invalid printerID";

	std::cout << "Printer " << printerID << " finished job " 
		<< job.jobID << " at time " << current_time << std::endl;


	if ( !jobs_in_queue.empty() )
	{ //immediately assign another job
		std::cout << "Printer " << printerID << " assigned new job " 
			<< jobs_in_queue.top().first.jobID << " at time " << current_time << std::endl;
		EventJobFinished *new_job = new EventJobFinished(current_time + (jobs_in_queue.top().first.size / it->second.second), printerID, jobs_in_queue.top().first, this);
		psim->AddEvent(new_job);
		jobs_in_queue.pop();
	}
	else
	{ // no jobs in the queue - printer rests
		++num_available_printers;
		it->second.first = true;
	}
}

/* \brief Called when a new job arrives in the queue.
 *
 * \param current_time
 * 	The time the new job arrived in the queue.
 *
 * \param job
 * 	The job to process.
 */
void PrintQueue::NewJobArrived( double current_time, PrintJob job )
{
	std::cout << "New job " << job.jobID 
		<< " at time " << current_time << std::endl;

	if ( num_available_printers>0 )
	{ //self-explanatory
		//find an available printer
		ID2pair::iterator it = printer_status.begin();
		while ( it != printer_status.end() && it->second.first==false ) {++it;}

		//if condition holds, we have a problem with data: 
		//num_available_printers>0 but no printer seem to be available
		if (it==printer_status.end()) throw "corrupted data";

		EventJobFinished *new_job = new EventJobFinished(current_time + (job.size / it->second.second), it->first, job, this);
		psim->AddEvent(new_job);
		--num_available_printers;
		it->second.first = false;

		std::cout << "Job assigned to printer " << it->first
			<< " at time " << current_time << std::endl;
	}
	else
	{ 
		std::cout << "No available printers - put in print queue\n";
		jobs_in_queue.push(std::pair<PrintJob,double>(job, current_time));
	}
}

////////////////////////////////////////////////////////////
/* EventJobFinished implementation */
////////////////////////////////////////////////////////////

/* \brief Constructor.
 *
 * \param _when
 * 	The time when this event is expected to be completed.
 *
 * \param _printer_id
 * 	The ID of the printer that the event is assigned to.
 *
 * \param _job
 * 	The job to be processed.
 *
 * \param _p_print_queue
 * 	A pointer to the print queue calling this event.
 */
EventJobFinished::EventJobFinished(double _when, int _printer_id, const PrintJob &_job, PrintQueue *_p_print_queue)
	:printer_id(_printer_id), job(_job), p_print_queue(_p_print_queue)
{
	SetWhen(_when);
}

/* \brief Executes the event.
 */
void EventJobFinished::Execute(void)
{
	p_print_queue->JobFinished(When(), printer_id, job);
}

////////////////////////////////////////////////////////////
/* EventNewJobArrived implementation */
////////////////////////////////////////////////////////////

/* \brief Constructor.
 *
 * \param _when
 * 	The time this event was created.
 *
 * \param _job
 * 	The job to be processed.
 *
 * \param _p_print_queue
 * 	The print queue that called this event.
 *
 * \param _p_method
 * 	The function to call to execute the event.
 */
EventNewJobArrived::EventNewJobArrived(double _when, const PrintJob& _job, PrintQueue* _p_print_queue, void (PrintQueue::*_p_method)(double,PrintJob))
	:job(_job), p_print_queue(_p_print_queue), p_method(_p_method)
{
	SetWhen(_when);
}

/* \brief Executes the event.
 */
void EventNewJobArrived::Execute(void)
{
	(p_print_queue->*p_method)(When(), job);
}

