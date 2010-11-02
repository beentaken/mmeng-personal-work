#include "simulator.h"
#include "print_queue.h"
#include "cstdio"

void test0() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1001,20); 	// printer ID 1001, 
																// speed 20 pput (pages per unit of time)
	//create an event: new print job of id=1, low priority, and size 200 pages 
	//arrives at time 3.0
	sim.AddEvent( new EventNewJobArrived( 3.0,
				PrintJob(1,PrintJob::LOW,200) ,&pq,&PrintQueue::NewJobArrived));

	sim.Start();
}

void test1() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1001,20); 	// printer ID 1001, 
																// speed 20 pput (pages per unit of time)

	//create an event: new print job of id=1, low priority, and size 200 pages 
	//arrives at time 3.0
	sim.AddEvent( new EventNewJobArrived( 3.0,
				PrintJob(1,PrintJob::LOW,200) ,&pq,&PrintQueue::NewJobArrived));
	//more events (possibly out of order)
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(2,PrintJob::LOW,300) ,&pq,&PrintQueue::NewJobArrived));

	sim.Start();
}

void test2() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1001,20); 	// printer ID 1001, 
																// speed 20 pput (pages per unit of time)

	//first job immediately assigned to a printer
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(1,PrintJob::LOW,200) ,&pq,&PrintQueue::NewJobArrived));
	//this 3 jobs form a line ordered by priority (time is same), 
	//order should be 4 3 2
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(2,PrintJob::LOW,200) ,&pq,&PrintQueue::NewJobArrived));
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(4,PrintJob::HIGH,300),&pq,&PrintQueue::NewJobArrived));
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(3,PrintJob::MEDIUM,600) ,&pq,&PrintQueue::NewJobArrived));

	sim.Start();
}

void test3() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1001,20); 	// printer ID 1001, 
																// speed 20 pput (pages per unit of time)

	//first job immediately assigned
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(1,PrintJob::LOW,200) ,&pq,&PrintQueue::NewJobArrived));
	//this 3 jobs form a line ordered by priority, then by time
	//order is 4 3 2 5
	sim.AddEvent( new EventNewJobArrived( 1.0,
				PrintJob(5,PrintJob::LOW,200) ,&pq,&PrintQueue::NewJobArrived));
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(2,PrintJob::LOW,200) ,&pq,&PrintQueue::NewJobArrived));
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(4,PrintJob::HIGH,300),&pq,&PrintQueue::NewJobArrived));
	sim.AddEvent( new EventNewJobArrived( 0.0,
				PrintJob(3,PrintJob::MEDIUM,600) ,&pq,&PrintQueue::NewJobArrived));

	sim.Start();
}

void test4() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1,20);
	pq.RegisterPrinter(2,10);


	int job_id=0;
	for (double t=0.0; t<10.0;t+=2) { //jobs are rare - printer 2 never used
		sim.AddEvent( new EventNewJobArrived( t,
					PrintJob(++job_id,PrintJob::LOW,20),&pq,&PrintQueue::NewJobArrived));
	}

	sim.Start();
}

void test5() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1,20);
	pq.RegisterPrinter(2,10);


	int job_id=0;
	for (double t=0.0; t<10.0;t+=0.8) { // printer 2 used sometimes
		sim.AddEvent( new EventNewJobArrived( t,
					PrintJob(++job_id,PrintJob::LOW,20),&pq,&PrintQueue::NewJobArrived));
	}

	sim.Start();
}

void test6() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1,20);
	pq.RegisterPrinter(2,10);


	int job_id=0;
	for (double t=0.0; t<10.0;t+=0.2) { // printer 2 used always
		sim.AddEvent( new EventNewJobArrived( t,
					PrintJob(++job_id,PrintJob::LOW,20),&pq,&PrintQueue::NewJobArrived));
	}

	sim.Start();
}

void test7() {
	Simulator sim;
	PrintQueue pq(&sim);
	pq.RegisterPrinter(1001,20); 	// printer ID 1001, 
																// speed 20 pput (pages per unit of time)
	pq.RegisterPrinter(2001,30); 	// printer ID 2001, speed 30 
	pq.RegisterPrinter(2008,10); 	// printer ID 2008, speed 10 


	int job_id=0;
	for (double t=0.0; t<100.0;t+=1.01) {
		sim.AddEvent( new EventNewJobArrived( t,
					PrintJob(++job_id,PrintJob::LOW,20),&pq,&PrintQueue::NewJobArrived));
	}
	for (double t=0.0; t<100.0;t+=0.33) {
		sim.AddEvent( new EventNewJobArrived( t,
					PrintJob(++job_id,PrintJob::MEDIUM,10),&pq,&PrintQueue::NewJobArrived));
	}
	for (double t=0.0; t<100.0;t+=3.33) {
		sim.AddEvent( new EventNewJobArrived( t,
					PrintJob(++job_id,PrintJob::HIGH,25),&pq,&PrintQueue::NewJobArrived));
	}

	sim.Start();
}

void (*pTests[])() = { test0,test1,test2,test3,test4,test5,test6,test7 };

int main (int argc, char ** argv) {
	if (argc >1) {
		int test = 0;
		std::sscanf(argv[1],"%i",&test);
		pTests[test]();
	}
	return 0;
}
