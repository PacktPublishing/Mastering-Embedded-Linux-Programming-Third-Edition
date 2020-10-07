#!/bin/bash

if [ $# -ne 2 ]; then
        echo "Usage: $0 [machine] [image]"
        echo "       machine is, e.g., beaglebone"
	echo "       image is, e.g., core-image-minimal"
        exit 1
fi

if [ -z BUILDDIR ]; then
	echo "Please source oe-init-build-env"
	exit 1
fi

BOOT_PART=/media/${USER}/boot
ROOTFS_PART=/media/${USER}/rootfs

MACHINE=$1
IMAGE=$2-${MACHINE}

IMAGES_DIR=tmp/deploy/images/${MACHINE}

if [ ! -d $BOOT_PART ]; then
	echo "Can't find $BOOT_PART on sdcard"
	exit 1
fi

if [ ! -d $ROOTFS_PART ]; then
	echo "Can't find $ROOTFS_PART on sdcard"
	exit 1
fi

cp ${IMAGES_DIR}/MLO ${BOOT_PART}
if [ $? -ne 0 ]; then echo "Error: dd"; exit 1; fi
cp ${IMAGES_DIR}/u-boot.img ${BOOT_PART}
if [ $? -ne 0 ]; then echo "Error: dd"; exit 1; fi

sudo tar -C $ROOTFS_PART -xf ${IMAGES_DIR}/${IMAGE}.tar.bz2
if [ $? -ne 0 ]; then echo "Error: dd"; exit 1; fi

echo "Success!"

