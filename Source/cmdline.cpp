#include "cmdline.h"
#include "client_server_header.h"

#include <malloc.h>
#include <cstring>
#include <cstdio>
#include <cctype>

#ifdef _WIN32
	#pragma warning (disable : 6387)	// value could be '0'
	#pragma warning (disable : 6011)	// derefencing nullptr
	#pragma warning (disable : 28183)	// same value (dumb error?)
#endif // _WIN32


cmdline_t* CreateCommandLine(int argc, char** argv)
{
	cmdline_t* cmdline = (cmdline_t*) malloc(sizeof(cmdline_t));
	memset(cmdline, 0, sizeof(cmdline_t));

	cmdline->argv	= argv;
	cmdline->ip		= NULL;
	cmdline->argc	= argc;
	cmdline->client = false;
	cmdline->server = false;

	return cmdline;
}

void DeleteCommandLine(cmdline_t* cmdline)
{
	free(cmdline);
	cmdline = nullptr;
}

bool ParseCommandLine(cmdline_t* cmdline)
{
	if (cmdline->argc <= 1 || cmdline->argv == nullptr)
	{
		return false;
	}

	for (int i = 1; i < cmdline->argc; i++)
	{
		if (strcmp(cmdline->argv[i], "-client") == 0 && cmdline->argv[i + 1] != NULL)
		{
			cmdline->client = true;
			cmdline->ip = cmdline->argv[i + 1];
		}
		else if (strcmp(cmdline->argv[i], "-server") == 0)
		{
			cmdline->server = true;
		}
	}

	if ((!cmdline->client && !cmdline->server) || (cmdline->client && cmdline->server))
	{
		// Can't be none or both!
		return false;
	}

	return true;
}

void ExecuteCommandLine(cmdline_t* cmdline)
{
	if (cmdline->net & NET_CLIENT)
	{
		// TODO: Excute Client Program
		create_client_socket(cmdline->ip);
	}
	else if (cmdline->server)
	{
		// TODO: Excute Server program
		create_server_socket();
	}
}