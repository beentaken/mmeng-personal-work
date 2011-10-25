#include <stdio.h>  /* printf */
#include <string.h> /* strstr,strlen */
#include <stdlib.h> /* atoi for C++ compiler */
#include "splitter.h"


int main(int argc, char** argv) {
	int join=0,split=0;
	char *output="";
	int size=0,stop=0;

	if (argc<2) { 
		printf("Usage:\n\t%s -j -o <output file> -i <filename>\nto join\ror \
				\n\t%s -s <size in bytes> -o <output file suffix> -i <filenames>\n \
				to split\n\n",argv[0],argv[0]);
	}

	while ( !stop && *++argv ) {
		if (strlen(*argv)>1) {
			switch ((*argv)[1]) {
				case 's': size=atoi(*++argv); split=1; break;
				case 'j': join=1; break;
				case 'o': output=*++argv; break;
				case 'i': ++argv; stop=1; break;/* the rest of argv is just a list of 
																				 * files, so -i is always the last*/
			}
		}
	}

	if (split) {
		return SplitFile(argv[0],output,size);
	}
	if (join) {
		return JoinFiles(argv,output);
	}
	return E_NO_ACTION; /* no operation was specified*/
}

