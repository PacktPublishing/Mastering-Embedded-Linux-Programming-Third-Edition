/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Dummy char driver                                                         */
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

#define DEVICE_NAME "dummy"
#define MAJOR_NUM 42
#define NUM_DEVICES 4

static struct class *dummy_class;

static int dummy_open(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static int dummy_release(struct inode *inode, struct file *file)
{
	pr_info("%s\n", __func__);
	return 0;
}

static ssize_t dummy_read(struct file *file,
			char *buffer, size_t length, loff_t * offset)
{
	pr_info("%s %u\n", __func__, length);
	return 0;
}

static ssize_t dummy_write(struct file *file,
			 const char *buffer, size_t length, loff_t * offset)
{
	pr_info("%s %u\n", __func__, length);
	return length;
}

struct file_operations dummy_fops = {
	.owner = THIS_MODULE,
	.open = dummy_open,
	.release = dummy_release,
	.read = dummy_read,
	.write = dummy_write,
};

int __init dummy_init(void)
{
	int ret;
	int i;

	printk("Dummy loaded\n");
	ret = register_chrdev(MAJOR_NUM, DEVICE_NAME, &dummy_fops);
	if (ret != 0)
		return ret;

	dummy_class = class_create(THIS_MODULE, DEVICE_NAME);
	for (i = 0; i < NUM_DEVICES; i++) {
		device_create(dummy_class, NULL,
			      MKDEV(MAJOR_NUM, i), NULL, "dummy%d", i);
	}

	return 0;
}

void __exit dummy_exit(void)
{
	int i;

	for (i = 0; i < NUM_DEVICES; i++) {
		device_destroy(dummy_class, MKDEV(MAJOR_NUM, i));
	}
	class_destroy(dummy_class);

	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
	printk("Dummy unloaded\n");
}

module_init(dummy_init);
module_exit(dummy_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chris Simmonds");
MODULE_DESCRIPTION("A dummy driver");
