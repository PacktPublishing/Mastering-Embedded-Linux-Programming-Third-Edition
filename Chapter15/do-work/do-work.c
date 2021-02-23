/* Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk) */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

static volatile int quit_now = 0;
unsigned long loop_count;
sigset_t alarm_sig;

void sig_int_handler(int n)
{
	quit_now = 1;
}

static unsigned long waste_time(unsigned long v)
{
	unsigned long new_v;
	new_v = (v * 22)/7;
	return new_v;
}

static void calibrate(void)
{
	struct itimerval value;
	struct sigaction act;
	int i;

	act.sa_handler = sig_int_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, NULL);

	/* Create a 10ms timer */
	value.it_value.tv_sec = 0;
	value.it_value.tv_usec = 10000;
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_usec = 10000;
	if (setitimer(ITIMER_REAL, &value, NULL) != 0) {
		perror("Failed to set timer");
		exit(1);
	}

	/* See how many times we loop in 10 ms.
	   Let the timer expire 4 times and take the last count */
	for (i = 0; i < 4; i++) {
		quit_now = 0;
		loop_count = 0;
		while (!quit_now) {
			waste_time(123);
			loop_count++;
		}
	}
}

static void do_work(long msecs)
{
	unsigned long local_count;
	unsigned long end_count;

	local_count = 0;
	end_count = (loop_count * msecs)/10;
	while (local_count < end_count) {
		waste_time(123);
		local_count++;
	}
}

static void wait_next(long msecs)
{
	int sig;
	sigwait(&alarm_sig, &sig);
}

static void usage(void)
{
	printf("Usage: \n"
	       "    -c               calibrate: you need to do this first\n"
	       "    -l [loop count]  loop count from calibration\n"
	       "    -n [on count]    on (work) time in ms, default 10\n"
	       "    -f [off count]   off (sleep) time, default same as on time\n");
}

int main(int argc, char *argv[])
{
	int opt;
	unsigned long on_time_ms = 10;
	unsigned long off_time_ms = -1;
	struct itimerval value;

	if (argc == 1) {
		usage();
		exit(0);
	}

	while ((opt = getopt(argc, argv, "cf:l:n:")) != -1) {
		switch (opt) {
			case 'c':
				printf("Calibrating...\n");
				calibrate();
				printf("Now run %s -l %lu\n", argv[0], loop_count);
				exit(0);
				break;
			case 'f':
				off_time_ms = strtoul(optarg, NULL, 0);
				break;
			case 'l':
				loop_count = strtoul(optarg, NULL, 0);
				break;
			case 'n':
				on_time_ms = strtoul(optarg, NULL, 0);
				break;
			default:
				usage();
				exit(0);
		}
	}

	if (loop_count == 0) {
		usage();
		exit(0);
	}

	if (off_time_ms == -1)
		off_time_ms = on_time_ms;

	printf("working for %lu ms, sleeping for %lu ms\n",
		on_time_ms, off_time_ms);

	/* Block SIGALRM */
	sigemptyset (&alarm_sig);
	sigaddset (&alarm_sig, SIGALRM);
	sigprocmask (SIG_BLOCK, &alarm_sig, NULL);

	/* Create a timer */
	value.it_value.tv_sec = 0;
	value.it_value.tv_usec = (off_time_ms + on_time_ms) * 1000;
	value.it_interval.tv_sec = 0;
	value.it_interval.tv_usec = (off_time_ms + on_time_ms) * 1000;
	if (setitimer(ITIMER_REAL, &value, NULL) != 0) {
		perror("Failed to set timer");
		exit(1);
	}
	while (1) {
		do_work(on_time_ms);
		wait_next(off_time_ms);
	}

	return 0;
}
