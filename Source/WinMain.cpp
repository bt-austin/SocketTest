#include "cmdline.h"

#include <cstdio>
#include <cstdlib>


int main(int argc, char** argv)
{
	cmdline_t* cmdline = CreateCommandLine(argc, argv);

	if (!ParseCommandLine(cmdline))
	{
		printf("[ERROR]: Failed to parse command-line!\n");
		return EXIT_FAILURE;
	}

	ExecuteCommandLine(cmdline);
	DeleteCommandLine(cmdline);
	return EXIT_SUCCESS;
}