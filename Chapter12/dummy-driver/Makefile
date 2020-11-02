# Copyright (C) 2017, Chris Simmonds (chris@2net.co.uk)
#
# LINUXDIR should point to the kerenl you are running on the target.
# If you are building with Buildroot, you would type something like:

# export ARCH=arm
# export CROSS_COMPILE=arm-buildroot-linux-gnueabi-
# export LINUXDIR=/home/chris/buildroot/output/build/linux-4.9.6
# make 

# If you are compiling with a Yocto Project SDK, everything should
# be set up when you source the environment-setup scipt so you can
# just type:

# make

LINUXDIR ?= $(SDKTARGETSYSROOT)/usr/src/kernel

obj-m := dummy.o

all:
	make -C $(LINUXDIR) M=$(shell pwd)

clean:
	make -C $(LINUXDIR) M=$(shell pwd) clean

