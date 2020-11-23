/* Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>

static void sig_handler(int sig)
{
	printf("Cleaning up\n");
}

int main(int argc, char *argv[])
{
	time_t start;
	int f;
	char msg[64];

	printf("%s starting\n", argv[0]);

	f = open("/dev/kmsg", O_WRONLY);
	if (f == -1)
		printf("Failed to open /dev/kmsg: no messages from me!\n");

	if (argc == 2 && strcmp(argv[1], "-n") == 0) {
		printf("Not forking\n");
	} else {
		printf("Deamonizing...\n");
		if (daemon(0, 0) == -1) {
			perror("Daemon failed");
			return 1;
		}
	}

	signal(SIGHUP, sig_handler);

	start = time(NULL);
	while(1) {
		snprintf(msg, sizeof(msg), "%s has been running for %ld seconds\n",
			argv[0],
			time(NULL) - start);
		write(f, msg, strlen(msg));
		sleep(60);
	}
	return 0;
}
