#!/bin/bash

KERNEL=zImage
DTB=versatile-pb.dtb
ROOTDIR=${HOME}/rootfs
HOST_IP=192.168.1.1
TARGET_IP=192.168.1.101
NET_NUMBER=192.168.1.0
NET_MASK=255.255.255.0

if [ ! -f ${KERNEL} ]; then
	echo "${KERNEL} does not exist"
	exit 1
fi
if [ ! -f ${DTB} ]; then
	echo "${DTB} does not exist"
	exit 1
fi

sudo tunctl -u $(whoami) -t tap0
sudo ifconfig tap0 ${HOST_IP}
sudo route add -net ${NET_NUMBER} netmask ${NET_MASK} dev tap0
sudo sh -c "echo 1 > /proc/sys/net/ipv4/ip_forward"

QEMU_AUDIO_DRV=none \
qemu-system-arm -m 256M -nographic -M versatilepb -kernel ${KERNEL} -append "console=ttyAMA0,115200 root=/dev/nfs rw nfsroot=${HOST_IP}:${ROOTDIR},v3 ip=${TARGET_IP}" -dtb ${DTB} -net nic -net tap,ifname=tap0,script=no
