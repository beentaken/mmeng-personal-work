/*!
\file   splitter.c
\author Marcus Meng
\par    email: marcus.meng\@digipen.edu
\par    DigiPen login: marcus.meng
\par    Course: CS225
\par    Assignment 1
\date   May 23, 2010
\brief
	This file contains implementations for the functions required to
	build a basic file splitter/joiner program.

Hours spent on this assignment: 2

Specific portions that gave you the most trouble:

Just figuring out how to detect the end of file reliably.

*/

#include <stdio.h> /* fopen/fread/fclose/fwrite. */
#include <stdlib.h> /* malloc/free. */
#include "splitter.h"

/*!
 * \brief Finds the correct size for the buffers used for input and output.
 *
 * Ascertains whether to use the size given or the maximum efficient chunk size
 * so that the computer doesn't have to worry about paging issues.
 *
 * \param size
 * 	The expected size of the chunks to be read.
 *
 * \return An appropriate size for a buffer expected to contain said chunks.
 */
static size_t get_buffer_size(const size_t size)
{
	if (size < MAX_CHUNK_SIZE)
		return(size);
	return(MAX_CHUNK_SIZE);
}

/*!
 * \brief Splits a file into the specified number of chunks.
 *
 * \param filename
 * 	The filename of the input file.
 *
 * \param output
 * 	The basic filename of the output chunks. Will have a number appended to it.
 *
 * \param size
 * 	The size of each output chunk. Must be larger than 0.
 *
 * \return FUNCTION_SUCCESS of there were no issues, an appropriate error code otherwise.
 */
int SplitFile(char* filename, char* output, size_t size)
{
	char current_file_name[MAX_FILENAME_LENGTH];
	int file_count=0;
	size_t bytes_read = size, chunk_position = 0;
	const size_t chunk_size = get_buffer_size(size);
	char *buffer; /* Holds data read. */
	FILE *in_file = fopen(filename, "rb"); /* Input file, read here. */

	/* Validate input file. */
	if (NULL == in_file)
	{
		return(E_BAD_SOURCE); /* BAD. */
	}

	/* Otherwise, we're good to go... */
	
	buffer = (char*)malloc(chunk_size);

	/* Validate buffer. */
	if (NULL == buffer)
	{
		return(E_NO_MEMORY);
	}


	/* Output filename string. */
	sprintf(current_file_name, "%s%04i", output, file_count);
	
	while (!feof(in_file))
	{
		if (chunk_position + chunk_size > size)
		{
			bytes_read = fread(buffer, BYTE, size - chunk_position, in_file);
			chunk_position = 0;
		}
		else
		{
			chunk_position += (bytes_read = fread(buffer, BYTE, chunk_size, in_file));
		}

		/* If we EOF after read it's bad and we won't do anything.
		 * But if we don't...
		 */
		if (bytes_read != 0 /*&& !feof(in_file)*/)
		{
			/* Set up output. */
			FILE* out_file = fopen(current_file_name, "ab");

			/* Validate output file handle. */
			if (NULL == out_file)
			{
				return(E_BAD_DESTINATION);
			}

			fwrite(buffer, BYTE, bytes_read, out_file);

			fclose(out_file);
		}

		if (0 == chunk_position)
		{
			sprintf(current_file_name, "%s%04i", output, ++file_count);
		}
	}
	free(buffer); /* Hygeine. */
	fclose(in_file);

	return FUNCTION_SUCCESS;	/* Return value is passed back to main. 0 is a normal exit. */
}

/*!
 * \brief Joins the files specified in the array of filenames given in the first arguments into one big file.
 *
 * \param filenames
 * 	A pointer to an array of null-terminated strings representing the filenames to process.
 *
 * \param output
 * 	The filename of the output file to consolidate the inputs into.
 *
 * \return FUNCTION_SUCCESS if there were no problems, an error code otherwise.
 */
int JoinFiles(char** filenames, char* output)
{
	/* Buffer to hold our current input. */
	char* buffer;
	size_t bytes_read;
	/* The output file. */
	FILE *out_file = fopen(output, "ab");

	/* Validate the output file handle. */
	if (NULL == out_file)
	{
		return(E_BAD_DESTINATION);
	}

	/* Validate buffer. */
	buffer = (char*)malloc(MAX_CHUNK_SIZE);

	if (NULL == buffer)
	{
		fclose(out_file); /* Try to leave things in a reasonable state. */
		return(E_NO_MEMORY);
	}

	/* All is well, let's go... */

	printf("join\n");
	while (*filenames)
	{
		/* Let's get some input. */
		FILE *in_file = fopen(*filenames, "rb");

		/* Validate! VALIDATE! */
		if (NULL == in_file)
		{
			free(buffer);
			fclose(out_file);
			return(E_BAD_SOURCE);
		}

		/* All's right in the world. */
		
		while (0 != (bytes_read = fread(buffer, BYTE, MAX_CHUNK_SIZE, in_file)))
		{
			if (bytes_read > 0 /*&& !feof(in_file) */)
			{
				fwrite(buffer, BYTE, bytes_read, out_file);
			}
		}

		fclose(in_file);

		printf("%s\n",*filenames++);
	}
	printf("into %s\n",output);

	free(buffer);
	fclose(out_file);

	return FUNCTION_SUCCESS;
}

