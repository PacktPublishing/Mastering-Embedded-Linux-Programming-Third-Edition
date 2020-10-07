DESCRIPTION = "A friendly program that prints Hello World!" 
PRIORITY = "optional" 
SECTION = "examples" 

LICENSE = "GPLv2" 
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6" 

SRC_URI = "file://helloworld.c" 

S = "${WORKDIR}"
 
do_compile() { 
	${CC} ${CFLAGS} ${LDFLAGS} helloworld.c -o helloworld
} 

do_install() { 
	install -d ${D}${bindir} 
	install -m 0755 helloworld ${D}${bindir} 
}

