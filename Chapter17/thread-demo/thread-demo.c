/* Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk) */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

static void *thread_fn(void *arg)
{
	printf("New thread started, PID %d TID %d\n",
		getpid(), (pid_t)syscall(SYS_gettid));
	sleep(10);
	printf("New thread terminating\n");
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t t;

	printf("Main thread, PID %d TID %d\n",
		getpid(), (pid_t)syscall(SYS_gettid));
	pthread_create(&t, NULL, thread_fn, NULL);
	pthread_join(t, NULL);
	return 0;
}
