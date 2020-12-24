/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Mailbox driver                                                            */
/*                                                                           */
/* Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk)                     */
/*                                                                           */
/* This program is free software; you can redistribute it and/or modify      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU          */
/* General Public License for more details.                                  */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* along with this program; if not, write to the Free Software               */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA   */
/*                                                                           */
/* ------------------------------------------------------------------------- */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <asm/uaccess.h>
#include <asm/errno.h>

#define DEVICE_NAME "mbx"
#define MAJOR_NUM 42
#define NUM_MAILBOXES 4
#define MBX_LEN 1024

/* Define this macro to cause an oops on read or write */
#define GO_OOPS 1

struct mbx_data {
	char *mbx;
	int mbx_len;
	wait_queue_head_t wq;
};

static struct mbx_data mailboxes[NUM_MAILBOXES];
static struct class *mbx_class;

static int mbx_open(struct inode *inode, struct file *file)
{
	if (MINOR(inode->i_rdev) >= NUM_MAILBOXES) {
		printk("Invalid mbx minor number\n");
		return -ENODEV;
	}
#ifndef GO_OOPS
	file->private_data = &mailboxes[MINOR(inode->i_rdev)];
#endif
	return 0;
}

static int mbx_release(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t mbx_read(struct file *file,
			char *buffer, size_t length, loff_t * offset)
{
	struct mbx_data *m = (struct mbx_data *)file->private_data;
	int len;
	int ret;

	if (m->mbx_len == 0) {
		if (file->f_flags & O_NONBLOCK)
			return -EAGAIN;
		ret = wait_event_interruptible(m->wq, m->mbx_len > 0);
		if (ret != 0) {
			return ret;
		}
	}

	len = m->mbx_len;
	if (len > length)
		len = length;
	if (copy_to_user(buffer, m->mbx, m->mbx_len) != 0) {
		printk("copy_to_user failed\n");
		return -EFAULT;
	}
	m->mbx_len = 0;
	return len;
}

static ssize_t mbx_write(struct file *file,
			 const char *buffer, size_t length, loff_t * offset)
{
	struct mbx_data *m = (struct mbx_data *)file->private_data;

	if (length > MBX_LEN)
		length = MBX_LEN;
	m->mbx_len = length;
	if (copy_from_user(m->mbx, buffer, length) != 0) {
		printk("copy_from_user failed\n");
		return -EFAULT;
	}
	wake_up_interruptible(&m->wq);
	return length;
}

static unsigned int mbx_poll(struct file *file, poll_table * wait)
{
	struct mbx_data *m = (struct mbx_data *)file->private_data;
	unsigned int mask = 0;

	poll_wait(file, &m->wq, wait);

	/* See if there is any data to read */
	if (m->mbx_len > 0)
		mask |= (POLLIN | POLLRDNORM);

	/* Writing is always possible */
	mask |= (POLLOUT | POLLWRNORM);

	return mask;
}

static long mbx_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
        int ret = 0;

	return ret;
}

struct file_operations mbx_fops = {
	.owner = THIS_MODULE,
	.open = mbx_open,
	.release = mbx_release,
	.read = mbx_read,
	.write = mbx_write,
	.poll = mbx_poll,
	.unlocked_ioctl = mbx_ioctl
};

int __init mbx_init(void)
{
	int ret;
	int i;

	printk("Mailbox loaded\n");
	ret = register_chrdev(MAJOR_NUM, DEVICE_NAME, &mbx_fops);
	if (ret != 0)
		return ret;

	/* Create a "mbx" class which will show up as /sys/class/mbx. The main
	   benefit will be to cause udev/mdev to create the appropriate
	   device node in/dev */
	mbx_class = class_create(THIS_MODULE, DEVICE_NAME);
	for (i = 0; i < NUM_MAILBOXES; i++) {
		mailboxes[i].mbx_len = 0;
		init_waitqueue_head(&mailboxes[i].wq);
		device_create(mbx_class, NULL,
			      MKDEV(MAJOR_NUM, i), NULL, "mbx%d", i);
	}

	return 0;
}

void __exit mbx_exit(void)
{
	int i;

	for (i = 0; i < NUM_MAILBOXES; i++) {
		device_destroy(mbx_class, MKDEV(MAJOR_NUM, i));
	}
	class_destroy(mbx_class);

	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
	printk("Mailbox unloaded\n");
}

module_init(mbx_init);
module_exit(mbx_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Simmonds");
MODULE_DESCRIPTION("A sort of mailbox");
