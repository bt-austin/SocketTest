#ifndef CMDLINE_H
#define CMDLINE_H

#define NET_CLIENT 1
#define NET_SERVER 2
#define NET_UNKNOWN 3

struct cmdline_t
{
	char**	argv;
	char*	ip;
	int		argc;
	bool	client;
	bool	server;
};

cmdline_t* CreateCommandLine(int argc, char** argv);
void DeleteCommandLine(cmdline_t* cmdline);

bool ParseCommandLine(cmdline_t* cmdline);
void ExecuteCommandLine(cmdline_t* cmdline);

#endif // !CMDLINE_H