#!/bin/bash

PATH=${HOME}/x-tools/arm-unknown-linux-gnueabi/bin/:$PATH

cd linux-stable
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- mrproper
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make versatile_defconfig
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make -j4 ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- zImage
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make -j4 ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- modules
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- dtbs
if [ $? != 0 ]; then echo "ERROR"; exit; fi

