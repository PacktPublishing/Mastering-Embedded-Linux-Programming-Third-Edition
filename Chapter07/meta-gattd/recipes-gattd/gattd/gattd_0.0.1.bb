# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

DESCRIPTION = "Python BLE GATT server"
HOMEPAGE = "https://github.com/fvasquez/gattd"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI = "https://github.com/fvasquez/gattd/archive/v${PV}.tar.gz"
SRC_URI[md5sum] = "09104711e63aa8e91ce6ab767f646570"
SRC_URI[sha1sum] = "93627f7daa8a621694782efc89bba9caebd9f58f"
SRC_URI[sha256sum] = "b1bcdd426b67f45b4360d9f5cadc8fe5145a799fe5349f1998d8a0d0cd896642"
SRC_URI[sha384sum] = "009ca499e55d1ca378ab4ac40f710a9b49d1278c8438222dfd9340d1604c41b13b8b54432a33cc03300db9c3dac35e46"
SRC_URI[sha512sum] = "eb60f86e13dec09d547b76eea2c56b946cb880003a6d3675deb9b1d0937489f6025ee73ea59e60f3071a343d8baefc4d6c14800a3d889598604a92a1ad11bfc8"

RDEPENDS_${PN} = "python3-dbus"

S = "${WORKDIR}/gattd-${PV}"

