/*!
\file   splitter.h
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 1
\date   May 23, 2010
\brief
	This file contains prototypes for the functions required to
	build a basic file splitter/joiner program.
*/

#ifndef SPLITTER_H
#define SPLITTER_H

#ifdef __cplusplus
extern "C"
{
#endif

#define BYTE 1
#define MAX_FILENAME_LENGTH 256
/* Page size efficiency, et al. */
#define MAX_CHUNK_SIZE 4096

/* Function exit codes. */
#define FUNCTION_SUCCESS 0

enum 
{E_BAD_SOURCE=1, E_BAD_DESTINATION, E_NO_MEMORY, E_NO_ACTION, E_SMALL_SIZE};

int SplitFile(char*  filename,  char* output, size_t size);
int JoinFiles(char** filenames, char* output);

#ifdef __cplusplus
}
#endif

#endif /* SPLITTER_H */

