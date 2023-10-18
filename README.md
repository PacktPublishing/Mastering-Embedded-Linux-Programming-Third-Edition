


# Mastering Embedded Linux Programming – Third Edition

<a href="https://www.packtpub.com/product/mastering-embedded-linux-programming-third-edition/9781789530384?utm_source=github&utm_medium=repository&utm_campaign=9781789530384"><img src="https://static.packt-cdn.com/products/9781789530384/cover/smaller" alt="Mastering Embedded Linux Programming – Third Edition" height="256px" align="right"></a>

This is the code repository for [Mastering Embedded Linux Programming – Third Edition](https://www.packtpub.com/product/mastering-embedded-linux-programming-third-edition/9781789530384?utm_source=github&utm_medium=repository&utm_campaign=9781789530384), published by Packt.

**Create fast and reliable embedded solutions with Linux 5.4 and the Yocto Project 3.1 (Dunfell)**

## What is this book about?
Embedded Linux runs many of the devices we use every day. From smart TVs and Wi-Fi routers to test equipment and industrial controllers, all of them have Linux at their heart. The Linux OS is one of the foundational technologies comprising the core of the Internet of Things (IoT). This book starts by breaking down the fundamental elements that underpin all embedded Linux projects: the toolchain, the bootloader, the kernel, and the root filesystem. After that, you will learn how to create each of these elements from scratch and automate the process using Buildroot and the Yocto Project.

This book covers the following exciting features: 
* Use Buildroot and the Yocto Project to create embedded Linux systems
* Troubleshoot BitBake build failures and streamline your Yocto development workflow
* Update IoT devices securely in the field using Mender or balena
* Prototype peripheral additions by reading schematics, modifying device trees, soldering breakout boards, and probing pins with a logic analyzer
* Interact with hardware without having to write kernel device drivers

If you feel this book is for you, get your [copy](https://www.amazon.com/dp/1789530385) today!

## Instructions and Navigations
All of the code is organized into folders. For example, `Chapter02`.

The code will look like the following:
```
if (test expression)
{
  Statement upon condition is true
}
```

**Following is what you need for this book:**
If you’re a systems software engineer or system administrator who wants to learn Linux implementation on embedded devices, then this book is for you. Embedded systems engineers accustomed to programming for low-power microcontrollers can use this book to help make the leap to high-speed systems on chips that can run Linux. Anyone responsible for developing new hardware that needs to run Linux will also find this book useful. Basic working knowledge of the POSIX standard, C programming, and shell scripting is assumed.

With the following software and hardware list you can run all code examples present in the book (Chapter 1-21).

### Software and Hardware List

| Chapters                      | Software/Hardware Required  | OS Required                   |
| ----------------------------- | --------------------------- | ----------------------------- |
| 3, 4, 5, 6, 9, 11, 12, 15, 21 | BeagleBone Black            | Not Applicable |
| 4, 6, 7, 10, 14, 19, 20       | Raspberry Pi 4              | Not Applicable |
| 4, 5, 6                       | QEMU (32-bit arm)           | Linux (Any) |
| 6, 7, 8, 10, 13, 19, 21          | Yocto Project 3.1 (Dunfell) | Compatible Linux Distribution |
| 6, 12, 13, 14, 19, 20, 21     | Buildroot 2020.02 LTS       | Linux (Any) |
| 2, 3, 4, 5                    | Crosstool-NG 1.24.0         | Linux (Any) |
| 3, 9                          | U-Boot v2021.01             | Linux (Any) |
| 4                             | Linux Kernel 5.4            | Linux (Any) |

We also provide a PDF file that has color images of the screenshots/diagrams used in this book. [Click here to download it](http://www.packtpub.com/sites/default/files/downloads/9781789530384_ColorImages.pdf).

## Errata

**Preface**: In the **Download Color Images** section link `https://static.packt-cdn.com/downloads/9781801071000_ColorImages.pdf` _should be_ https://static.packt-cdn.com/downloads/9781789530384_ColorImages.pdf 

**Page 26**: The `crosstool-ng-1.24.0` tag of crosstool-ng no longer builds because its `expat-2.2.6` and `isl-0.20` dependencies were relocated to different hosts. The simplest fix is to clone the latest version of the crosstool-ng source from the master branch of the Git repo.

```bash
$ git clone https://github.com/crosstool-ng/crosstool-ng.git
$ cd crosstool-ng
$ ./bootstrap
$ ./configure --prefix=${PWD}
$ make
$ make install
```

When crosstool-ng's maintainers tag a release after 1.24.0 readers can downgrade to that for stability.

**Page 43**: http://www.sqlite.org/2020/sqlite-autoconf-3330000.tar.gz may be no longer available. Replace it with an up-to-date source code URL from [SQLite Download Page](https://www.sqlite.org/download.html) and adjust the subsequent `tar` and `cd` commands' arguments.

**Page 44**: The path where the SQLite header files are installed is wrong. Here is their correct location.

* `<sysroot>/usr/include`: `sqlite3.h`, `sqlite3ext.h`: These are the header files.

**Page 55**: TI's x-loader code was integrated into upstream U-Boot back a long time ago. There should be no mention of it when discussing open source SPLs.

**Page 67**: "which would be `sdb` in the first example" should use `sda` instead.

**Page 105**: The link to the web page where you can download the prebuilt toolchain targeting AArch64 is broken. Here is a working [link](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads).

**Page 107**: The exercise on building a kernel for QEMU is missing a critical step where the `versatile_defconfig` is selected and a `.config` file is generated prior to compiling.

```bash
$ cd linux-stable
$ make ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- mrproper
$ make ARCH=arm versatile_defconfig
$ make -j4 ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- zImage
$ make -j4 ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- modules
$ make ARCH=arm CROSS_COMPILE=arm-unknown-linux-gnueabi- dtbs
```

These commands are also captured in a `build-linux-versatilepb.sh` script under the `Chapter04` directory.

**Page 109**: The exercise where we boot Linux for the first time on the BeagleBone Black is missing the serial baud rate from the kernel boot parameters. Before entering `bootz 0x80200000 - 0x80f00000` at the U-Boot prompt enter the following command:

```
setenv bootargs console=ttyO0,115200
```

This command replaces the incomplete `setenv bootargs console=ttyO0` command that was printed on that page of the book. The baud rate (`115200` in this case) needs to match the setting used in the host terminal program (e.g. `gtkterm`, `minicom`, or `screen`) otherwise we won't see any messages after `Starting the kernel ...` in the serial console.

Some readers have remarked that the letter `O` in `console=ttyO0` looks like a typo and asked if the `console` kernel boot parameter should instead be set to `tty00` with two zeros. The answer is no, `console=ttyO0` is in fact not a typo and `console=tty00` is never a valid option. Nowadays, it is best to use `console=ttyS0` with TI boards like the BeagleBone Black.

There are two kernel configuration options for the serial driver on the TI AM335x: either `SERIAL_8250_OMAP` or the generic `SERIAL_8250`. The OMAP driver is preferable because is supports additional features, but for a serial console it really makes no difference. In older versions of Linux, the OMAP driver was named `ttyO` using the letter `O`, but code was added in Linux 3.18 to handle both `ttyS` and `ttyO`.

**Page 156**: The commands for mounting a root filesystem on QEMU and the BeagleBone Black using NFS are missing the `v3` option from the `nfsroot` kernel boot parameter.

The QEMU start command should look like this:

```
QEMU_AUDIO_DRV=none \
qemu-system-arm -m 256M -nographic -M versatilepb -kernel ${KERNEL} -append "console=ttyAMA0,115200 root=/dev/nfs rw nfsroot=${HOST_IP}:${ROOTDIR},v3 ip=${TARGET_IP}" -dtb ${DTB} -net nic -net tap,ifname=tap0,script=no
```

The U-Boot commands should look like this:

```
setenv serverip <host IP>
setenv ipaddr <target IP>
setenv npath <path to staging directory>
setenv bootargs console=ttyO0,115200n8 root=/dev/nfs rw nfsroot=${serverip}:${npath},v3 ip=${ipaddr}
fatload mmc 0:1 0x80200000 zImage
fatload mmc 0:1 0x80f00000 am335x-boneblack.dtb
bootz 0x80200000 - 0x80f00000
```

Replace `<host IP>`, `<target IP>`, and `<path to staging directory>` with their actual values. Note that these same placeholder values also need to be updated in the `run-qemu-nfsroot.sh` and `uEnv.txt` scripts for `Chapter05`.

**Page 554**: To cross-compile the `shared-mem-demo` example program for Arm Cortex-A8 SoCs:

```bash
$ arm-cortex_a8-linux-gnueabihf-gcc shared-mem-demo.c -lrt -pthread \
-o shared-mem-demo
```

The command printed in the book generates an executable named `arm-cortex_a8-linux-gnueabihf-gcc` by mistake.

## Related products <Other books you may enjoy>
* Linux Device Drivers Development  [[Packt]](https://www.packtpub.com/product/linux-device-drivers-development/9781785280009?utm_source=github&utm_medium=repository&utm_campaign=9781785280009) [[Amazon]](https://www.amazon.com/dp/1785280007)

* Hands-On RTOS with Microcontrollers [[Packt]](https://www.packtpub.com/product/hands-on-rtos-with-microcontrollers/9781838826734?utm_source=github&utm_medium=repository&utm_campaign=9781838826734) [[Amazon]](https://www.amazon.com/dp/1838826734)

## Get to Know the Authors
**Frank Vasquez** is a Staff Embedded Software Engineer at Element Energy. He has over a decade of experience designing and building embedded Linux systems. During that time, he has shipped numerous devices including a rackmount DSP audio server, a diver-held sonar camcorder, and a consumer IoT hotspot. Before his career as an embedded Linux engineer, Frank was a database kernel developer at IBM where he worked on Db2. He lives in Silicon Valley.

**Chris Simmonds** is a software consultant and trainer living in southern England. He has almost two decades of experience in designing and building open-source embedded systems. He is the founder and chief consultant at 2net Ltd, which provides professional training and mentoring services in embedded Linux, Linux device drivers, and Android platform development. He has trained engineers at many of the biggest companies in the embedded world, including ARM, Qualcomm, Intel, Ericsson, and General Dynamics. He is a frequent presenter at open source and embedded conferences, including the Embedded Linux Conference and Embedded World.

## Other books by the authors
* [Mastering Embedded Linux Programming - Second Edition](https://www.packtpub.com/product/mastering-embedded-linux-programming-second-edition/9781787283282?utm_source=github&utm_medium=repository&utm_campaign=9781787283282)
* [Mastering Embedded Linux Programming](https://www.packtpub.com/product/mastering-embedded-linux-programming/9781784392536?utm_source=github&utm_medium=repository&utm_campaign=9781784392536)
### Download a free PDF

 <i>If you have already purchased a print or Kindle version of this book, you can get a DRM-free PDF version at no cost.<br>Simply click on the link to claim your free PDF.</i>
<p align="center"> <a href="https://packt.link/free-ebook/9781789530384">https://packt.link/free-ebook/9781789530384 </a> </p>
