# Recipe for ti-linux-kernel, with some customization to enable
# power management features on settings for AM335x/Beaglebone

inherit kernel
require recipes-kernel/linux/linux-yocto.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-4.1:"

# Add run-time dependency for PM firmware to the rootfs
DEPENDS = " amx3-cm3"

KERNEL_DEVICETREE_ti33x = "am335x-boneblack.dtb"

# Select 4.1 because later versions seem to have lost some
# features
LINUX_VERSION ?= "4.1"

COMPATIBLE_MACHINE = "beaglebone"

S = "${WORKDIR}/git"

BRANCH = "ti-linux-4.1.y"

SRCREV = "b56fa3bd73d45ef31478b7e3ab97570a0dd79c44"
PV = "4.1.37+git${SRCPV}"

# Append to the MACHINE_KERNEL_PR so that a new SRCREV will cause a rebuild
MACHINE_KERNEL_PR_append = "a"
PR = "${MACHINE_KERNEL_PR}"

KERNEL_GIT_URI = "git://git.ti.com/ti-linux-kernel/ti-linux-kernel.git"
KERNEL_GIT_PROTOCOL = "git"
SRC_URI += "${KERNEL_GIT_URI};protocol=${KERNEL_GIT_PROTOCOL};branch=${BRANCH} \
            file://defconfig"

# Copy the PMIC firmware into the kernel source so that it can be
# built in to the kernel image.
# This is not an elegant solution; but it works
do_compile_prepend() {
	cp ${STAGING_DIR_HOST}/lib/firmware/am335x-pm-firmware.elf ${STAGING_KERNEL_DIR}/firmware
	cp ${STAGING_DIR_HOST}/lib/firmware/am335x-bone-scale-data.bin ${STAGING_KERNEL_DIR}/firmware
}
