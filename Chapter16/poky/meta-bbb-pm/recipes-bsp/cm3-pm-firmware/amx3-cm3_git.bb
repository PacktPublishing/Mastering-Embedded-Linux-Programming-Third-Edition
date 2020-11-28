DESCRIPTION = "Cortex-M3 binary blob for suspend-resume"

LICENSE = "TI-TSPA"
LIC_FILES_CHKSUM = "file://License.txt;md5=7bdc54a749ab7a7dea999d25d99a41b8"

PV = "1.9.2"
PR = "r0"

SRCREV = "7eb9c0856a9e8b3b42bf64f761da135852b8eea7"
BRANCH ?= "ti-v4.1.y"

SRC_URI = "git://git.ti.com/processor-firmware/ti-amx3-cm3-pm-firmware.git;protocol=git;branch=${BRANCH}"

S = "${WORKDIR}/git"

FLOATABI = "${@bb.utils.contains("TUNE_FEATURES", "vfp", bb.utils.contains("TUNE_FEATURES", "callconvention-hard", " -mfloat-abi=hard", " -mfloat-abi=softfp", d), "" ,d)}"

do_compile() {
	make CROSS_COMPILE="${TARGET_PREFIX}" CC="${TARGET_PREFIX}gcc ${TOOLCHAIN_OPTIONS} ${FLOATABI}"
}

do_install() {
	install -d ${D}${base_libdir}/firmware
	install -m 0644 bin/am335x-pm-firmware.elf ${D}${base_libdir}/firmware/
	install -m 0644 bin/*-scale-data.bin ${D}${base_libdir}/firmware/
}

FILES_${PN} += "${base_libdir}/firmware"
