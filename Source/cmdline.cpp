#include "cmdline.h"
#include "ArenaAllocator.h"
#include "client_server_header.h"

#include <malloc.h>
#include <cstring>
#include <cstdio>

#ifdef _WIN32
	#pragma warning (disable : 6387)	// value could be '0'
	#pragma warning (disable : 6011)	// derefencing nullptr
	#pragma warning (disable : 28183)	// same value (dumb error?)
#endif // _WIN32

static ArenaAllocator* arena_allocator = nullptr;

cmdline_t* CreateCommandLine(int argc, char** argv)
{
	cmdline_t* cmdline = (cmdline_t*) malloc(sizeof(cmdline_t));
	memset(cmdline, 0, sizeof(cmdline_t));

	cmdline->argc = argc;
	cmdline->argv = argv;

	arena_allocator = new ArenaAllocator();
	return cmdline;
}

void DeleteCommandLine(cmdline_t* cmdline)
{
	arena_allocator->Deallocate(cmdline->ip);
	free(cmdline);
	cmdline = nullptr;
}

bool ParseCommandLine(cmdline_t* cmdline)
{
	if (cmdline->argc <= 1 || cmdline->argv == nullptr)
	{
		return false;
	}

	// Invalid index
	cmdline->net = 0;

	for (int i = 1; i < cmdline->argc; i++)
	{
		if (strcmp(cmdline->argv[i], "-app") == 0 && cmdline->argv[i + 1] != NULL)
		{
			char* app = cmdline->argv[i + 1];
			if (strcmp(app, "client") == 0)
			{
				cmdline->net |= NET_CLIENT;
			}
			else if (strcmp(app, "server") == 0)
			{
				cmdline->net |= NET_SERVER;
			}
		}
		else if (strcmp(cmdline->argv[i], "-ip") == 0 && cmdline->argv[i + 1] != NULL)
		{
			//
			// FIXME: Make sure that if no IP is passed, kill the program!
			//
			size_t len = strlen(cmdline->argv[i + 1]);
			cmdline->ip = static_cast<char*>(arena_allocator->Allocate(len * sizeof(char) + 1));
			strcpy(cmdline->ip, cmdline->argv[i + 1]);
		}
	}

	if (cmdline->net == 0)
	{
		// Failed to parse app...
		return false;
	}

	return true;
}

void ExecuteCommandLine(cmdline_t* cmdline)
{
	if (cmdline->net & NET_CLIENT)
	{
		// TODO: Excute Client Program
		create_client_socket(cmdline->argv);
	}
	else if (cmdline->net & NET_SERVER)
	{
		// TODO: Excute Server program
		create_server_socket(cmdline->argv);
	}
}