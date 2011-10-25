#include "printjob.h"

PrintJob::PrintJob( int _jobID, Priority _priority, double _size) : 
	jobID(_jobID), priority(_priority), size(_size) {}

bool PrintJob::operator< (const PrintJob& rhs) const {
	return priority<rhs.priority; 
}
