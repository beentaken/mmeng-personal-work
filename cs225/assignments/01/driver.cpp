#include <iostream> /* cout */
#include <string>   /* std::string */
#include <stdlib.h> /* atoi */
#include "splitter.h" /* splitter interface */

int main(int argc, char** argv) {
	int join=0,split=0;
	char *output=NULL;
	int size=0;

	if (argc<2) {
		std::cout << "Usage:\n\t" << argv[0] << " -j -o <output file> \
			      -i <filename>\nto join\ror\n\t" << argv[0] << " -s <size \
						in bytes> -o <output file suffix> -i <filenames>\n \
						to split\n\n";
	}

	bool stop=false;
	while ( !stop && *++argv ) {
		std::string str(*argv);
		if ( str.length() >1) {
			switch (str[1]) {
				case 's': size=atoi(*++argv); split=1; break;
				case 'j': join=1; break;
				case 'o': output=*++argv; break;
				case 'i': ++argv; stop=true; break;
			}
		}
	}

  if (split) {
    int ret = SplitFile(argv[0],output,size);
    return ret;
  }
  if (join) {
    int ret = JoinFiles(argv,output);
    return ret;
  }
	return E_NO_ACTION; /* no operation was specified*/
}

