/* Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char command_str[128];
	int pid;
	int child_status;
	int wait_for = 1;

	while (1) {
		printf("sh> ");
		scanf("%s", command_str);
		pid = fork();
		if (pid == 0) {
			/* child */
			printf("cmd '%s'\n", command_str);
			execl(command_str, command_str, (char *)NULL);
			/* We should not return from execl, so only get 
			   to this line if it failed */
			perror("exec");
			exit(1);
		}
		if (wait_for) {
			waitpid(pid, &child_status, 0);
			printf("Done, status %d\n", child_status);
		}
	}
	return 0;
}
