/* Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk) */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int f;
	unsigned int rnd;
	int n;

	f = open("/dev/urandom", O_RDONLY);
	if (f < 0) {
		perror("Failed to open urandom");
		return 1;
	}
	n = read(f, &rnd, sizeof(rnd));
	if (n != sizeof(rnd)) {
		perror("Problem reading urandom");
		return 1;
	}
	printf("Random number = 0x%x\n", rnd);
	close(f);
	return 0;
}

