# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
LICENSE = "LGPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=5f30f0716dfdd0d91eb439ebec522ec2"

SRC_URI = "https://github.com/containers/bubblewrap/releases/download/v${PV}/bubblewrap-${PV}.tar.xz"
SRC_URI[md5sum] = "1104b0e43006f22076b5057c129939c8"
SRC_URI[sha1sum] = "00e121950ea494fcd9cfbe23971c0938d6be6755"
SRC_URI[sha256sum] = "b9c69b9b1c61a608f34325c8e1a495229bacf6e4a07cbb0c80cf7a814d7ccc03"
SRC_URI[sha384sum] = "68c9ae7f0c8a13540ecd9b6647f307253022acca5267853ed5c497c6ea236f08fd9ce51016b8595eaa0af66f7bde92cf"
SRC_URI[sha512sum] = "0ff46dc0fda2d0cffbb36cc52ff43951b30cbd835a42cc56806acbbbd827796bfadbb1cfafc84d6b47a72c031ca44abe1c377acc0cc25fe3b33e854f5f687d35"

# NOTE: the following prog dependencies are unknown, ignoring: xsltproc
# NOTE: unable to map the following pkg-config dependencies: libselinux
#       (this is based on recipes that have previously been built and packaged)
DEPENDS = "libcap bash-completion"

# NOTE: if this software is not capable of being built in a separate build directory
# from the source, you should replace autotools with autotools-brokensep in the
# inherit line
inherit pkgconfig autotools

# Specify any options you want to pass to the configure script using EXTRA_OECONF:
EXTRA_OECONF = ""

FILES_${PN} += "/usr/share/*"
