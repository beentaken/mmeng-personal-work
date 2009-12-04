#include "tablen.h"

int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		show_tab_info(argv[1]);
		show_length_info(argv[1]);
	}

	return 0;
}

