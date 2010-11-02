#ifndef PRINTJOB_H
#define PRINTJOB_H

/* simple print job structure */
struct PrintJob {
	enum Priority {LOW,MEDIUM,HIGH};
	int jobID;  /* an ID - assigned by user. doesn't have to be unique, 
								 but it'll help if it is. */
	Priority priority; 
	double size; /* number of pages */
	PrintJob( int _jobID, Priority _priority = LOW, double _size = 100);	
	bool operator< (const PrintJob& rhs) const;
};
#endif

