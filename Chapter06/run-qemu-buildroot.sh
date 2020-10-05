#!/bin/bash

KERNEL=output/images/zImage
DTB=output/images/versatile-pb.dtb
ROOTFS=output/images/rootfs.ext2

if [ ! -f ${KERNEL} ]; then
	echo "${KERNEL} does not exist"
	exit 1
fi
if [ ! -f ${DTB} ]; then
	echo "${DTB} does not exist"
	exit 1
fi

qemu-system-arm -M versatilepb -m 256 \
-kernel ${KERNEL} \
-dtb ${DTB} \
-drive file=${ROOTFS},if=scsi,format=raw \
-append "root=/dev/sda console=ttyAMA0,115200" \
-serial stdio -net nic,model=rtl8139 -net user

