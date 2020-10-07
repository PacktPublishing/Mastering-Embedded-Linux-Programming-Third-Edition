#!/bin/bash
# Format a microSD card for the BeagelBone Black
# Mastering Embedded Linux Programming
# Copyright (c) Chris Simmonds, 2017

if [ $# -ne 1 ]; then
        echo "Usage: $0 [drive]"
        echo "       drive is 'sdb', 'mmcblk0', etc"
        exit 1
fi

function version_gt() { test "$(echo "$@" | tr " " "\n" | sort -V | head -n 1)" != "$1"; }

DRIVE=$1

# Check the drive exists in /sys/block
if [ ! -e /sys/block/${DRIVE}/size ]; then
	echo "Drive does not exist"
	exit 1
fi

# Check it is a flash drive (size < 32GiB)
NUM_SECTORS=`cat /sys/block/${DRIVE}/size`
if [ $NUM_SECTORS -eq 0 -o $NUM_SECTORS -gt 64000000 ]; then
	echo "/dev/$DRIVE does not look like an SD card, bailing out"
	exit 1
fi

# Unmount any partitions that have been automounted
if [ $DRIVE == "mmcblk0" ]; then
    sudo umount /dev/${DRIVE}*
    BOOT_PART=/dev/${DRIVE}p1
    ROOT_PART=/dev/${DRIVE}p2
else
    sudo umount /dev/${DRIVE}[1-9]
    BOOT_PART=/dev/${DRIVE}1
    ROOT_PART=/dev/${DRIVE}2
fi

# Overwite any existing partiton table with zeros
sudo dd if=/dev/zero of=/dev/${DRIVE} bs=1M count=10
if [ $? -ne 0 ]; then echo "Error: dd"; exit 1; fi

# Create 2 primary partitons on the sd card
#  1: FAT32, 64 MiB, boot flag
#  2: Linux, 1024 MiB
# Note that the parameters to sfdisk changed slightly v2.26
SFDISK_VERSION=`sfdisk --version | awk '{print $4}'`
if version_gt $SFDISK_VERSION "2.26"; then
	sudo sfdisk /dev/${DRIVE} << EOF
,64M,0x0c,*
,1024M,L,
EOF
else
	sudo sfdisk --unit M /dev/${DRIVE} << EOF
,64,0x0c,*
,1024,L,
EOF
fi
if [ $? -ne 0 ]; then echo "Error: sdfisk"; exit 1; fi

# Format p1 with FAT32 and p2 with ext4
sudo mkfs.vfat -F 16 -n boot ${BOOT_PART}
if [ $? -ne 0 ]; then echo "Error: mkfs.vfat"; exit 1; fi
sudo mkfs.ext4 -L rootfs ${ROOT_PART}
if [ $? -ne 0 ]; then echo "Error: mkfs.ext4"; exit 1; fi

echo "SUCCESS! Your microSD card has been formatted"
exit 0

