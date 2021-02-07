#!/bin/bash

set -e

git clone --depth=1 -b rpi-4.19.y https://github.com/raspberrypi/linux.git
svn export https://github.com/raspberrypi/firmware/trunk/boot

rm boot/kernel*
rm boot/*.dtb
rm boot/overlays/*.dtbo

PATH=${HOME}/gcc-arm-aarch64-none-linux-gnu/bin/:$PATH

cd linux

make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- bcm2711_defconfig
make -j4 ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu-

cp arch/arm64/boot/Image ../boot/kernel8.img
cp arch/arm64/boot/dts/overlays/*.dtbo ../boot/overlays/
cp arch/arm64/boot/dts/broadcom/*.dtb ../boot/

cat << EOF > ../boot/config.txt
enable_uart=1
arm_64bit=1
EOF

cat << EOF > ../boot/cmdline.txt
console=serial0,115200 console=tty1 root=/dev/mmcblk0p2 rootwait
EOF

