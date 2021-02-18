DESCRIPTION = "Python BLE GATT server"
HOMEPAGE = "https://github.com/fvasquez/gattd"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=c53d04442d1a229d62549856b7ec456a"

SRC_URI = "https://github.com/fvasquez/gattd/archive/v${PV}.tar.gz"
SRC_URI[md5sum] = "2a5ccd81395ba01534006b815b509c60"
SRC_URI[sha1sum] = "7a4b5fac479e2fade925c4baf53b3e643e320182"
SRC_URI[sha256sum] = "b6ff7bbe95517d0213ce376e7e72a92917b1645ccd995cc4e514c3b3c1a9bc39"
SRC_URI[sha384sum] = "7bf2e3e10ce057b792aa30de5e258ff911de64c8f7efbbee2af5c7dec5974c3fc2162d70335c31ed9c7010d14e459cdc"
SRC_URI[sha512sum] = "c2d0e436e8087d05b0c7017421100ae7b8c4d7ff812879cf9d4f7a5162860974bea49d24d711ecbb08e49ae4ae874d63e236a43e39fdd50c560417e85efb054b"

RDEPENDS_${PN} = "python3-dbus"

S = "${WORKDIR}/gattd-${PV}"

do_install () {
	install -d ${D}${bindir}
	install -m 0755 ${S}/*.py ${D}${bindir}
}

FILES_${PN} += "${bindir}/*.py"
