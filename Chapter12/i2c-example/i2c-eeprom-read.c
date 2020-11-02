/* Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk) */

/*
 * Sample program to read the first 4 bytes of the AT24C512B
 * 512 KiB EEPROM from the BeagleBone Black
 * The datasheet for the AT24C512B can be found at
 * http://www.atmel.com/Images/doc5297.pdf
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

/* Address of the EEPROM on the BeagleBone Black board */
#define I2C_ADDRESS 0x50

int main(void)
{
	int f;
	int n;
	char buf[10];

	/* Open the adapter and set the address of the I2C device */
	f = open("/dev/i2c-0", O_RDWR);
	if (f < 0) {
		perror("/dev/i2c-0:");
		return 1;
	}

	/* Set the address of the i2c slave device */
	if (ioctl(f, I2C_SLAVE, I2C_ADDRESS) == -1) {
		perror("ioctl I2C_SLAVE");
		return 1;
	}

	/* Set the 16-bit address to read (0) */
	buf[0] = 0;	/* address byte 1 */
	buf[1] = 0;	/* address byte 2 */
	n = write(f, buf, 2);
	if (n == -1) {
		perror("write");
		return 1;
	}

	/* Now read 4 bytes from that address */
	n = read(f, buf, 4);
	if (n == -1) {
		perror("read");
		return 1;
	}
	printf("0x%x 0x%x0 0x%x 0x%x\n",
		 buf[0], buf[1], buf[2], buf[3]);

	close(f);
	return 0;
}
