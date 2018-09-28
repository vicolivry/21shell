#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int		main(int argc, char **argv)
{
	int		pid;

	pid = getpid();
	if (argc == 2 && strcmp(argv[1], "-s") == 0)
		kill(pid, SIGSEGV);
	else if (argc == 2 && strcmp(argv[1], "-bp") == 0)
		kill(pid, SIGPIPE);
	else if (argc == 2 && strcmp(argv[1], "-a") == 0)
		kill(pid, SIGABRT);
	else
		printf("run with -s, -bp, -a\n");
	return (0);
}
