#!/bin/bash

PATH=${HOME}/x-tools/arm-cortex_a8-linux-gnueabihf/bin/:$PATH

cd linux-stable
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make ARCH=arm CROSS_COMPILE=arm-cortex_a8-linux-gnueabihf- mrproper
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make ARCH=arm multi_v7_defconfig
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make -j4 ARCH=arm CROSS_COMPILE=arm-cortex_a8-linux-gnueabihf- zImage
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make -j4 ARCH=arm CROSS_COMPILE=arm-cortex_a8-linux-gnueabihf- modules
if [ $? != 0 ]; then echo "ERROR"; exit; fi

make ARCH=arm CROSS_COMPILE=arm-cortex_a8-linux-gnueabihf- dtbs
if [ $? != 0 ]; then echo "ERROR"; exit; fi

