#include <stdio.h>
#include <string.h>

#define MAX_OUTPUT_LENGTH 75
#define MAX_INPUT_LENGTH 16

/*
000000 52 6F 73 65 73 20 61 72  65 20 72 65 64 2E 0D 0A   Roses are red...
 */
static void format(const char* inbuf, char *outbuf, int count, int start)
{
	int i; /* Loop counter. */
	int offset = 7; /* Index to start the hex dump at. */
	
	/* Set everything to a space by default. */
	memset(outbuf, ' ', MAX_OUTPUT_LENGTH);

	/* Print offset. */
	sprintf(outbuf, "%06X  ", start);

	for (i = 0; i < count; ++i)
	{
		/* Puts in that extra space after the 8th hex column. */
		if (8 == i)
			++offset;
		/* Position the format so that it overwrites the previous terminator. */
		sprintf(outbuf + (3 * i) + offset, "%02X  ", inbuf[i]);
	}

	/* Remove the terminator that sprintf adds. */
	outbuf[3 * i + offset + 1] = ' ';

	/* Dump inbuf into the end of outbuf. */
	strncpy(outbuf + (MAX_OUTPUT_LENGTH - MAX_INPUT_LENGTH - 1), inbuf, count);

	/* Replace nonprintables with a dot. */
	for (i = MAX_OUTPUT_LENGTH - MAX_INPUT_LENGTH - 1; i < MAX_OUTPUT_LENGTH; ++i)
	{
		if (outbuf[i] < 32 || outbuf[i] > 126)
		{
			outbuf[i] = '.';
		}
	}

	/* Add a newline and terminator at the end. */
	outbuf[MAX_OUTPUT_LENGTH - (MAX_INPUT_LENGTH - count) - 1] = '\n';
	outbuf[MAX_OUTPUT_LENGTH - (MAX_INPUT_LENGTH - count)] = '\0';
}

void dump(const char *filename)
{
	FILE *infile;         /* File pointer for input         */
	char inbuf[MAX_INPUT_LENGTH] = {0}; /* Read/format 16 bytes at a time */
	char outbuf[MAX_OUTPUT_LENGTH];      /* The longest formatted string   */

	/* Open the file for read/binary */
	infile = fopen(filename, "rb");

	if (infile)
	{
		long position = ftell(infile);
		printf("%s:\n", filename);

		while (!feof(infile))
		{
			/* Read in bytes (up to 16) using fread   */
			/* Format bytes using the format function */
			/* Print formatted string using printf    */
			int count = fread(inbuf, sizeof(char), MAX_INPUT_LENGTH, infile);
			format(inbuf, outbuf, count, position);
			printf("%s", outbuf);
			position = ftell(infile);
		}
	
		/* Close the file */
		fclose(infile);
	}
}

