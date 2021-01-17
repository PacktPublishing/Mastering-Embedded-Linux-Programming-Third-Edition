################################################################################
#
# bcc
#
################################################################################

BCC_VERSION = v0.16.0
BCC_SITE = https://github.com/iovisor/bcc.git
BCC_SITE_METHOD = git
BCC_GIT_SUBMODULES = YES
BCC_LICENSE = Apache-2.0
BCC_LICENSE_FILES = LICENSE.txt
# libbcc.so and libbpf.so
BCC_INSTALL_STAGING = YES
BCC_DEPENDENCIES = host-bison host-flex clang elfutils llvm python3 flex tar

# ENABLE_LLVM_SHARED=ON to use llvm.so.
# Force REVISION otherwise bcc will use git describe to generate a version number.
BCC_CONF_OPTS = -DENABLE_LLVM_SHARED=ON \
	-DREVISION=$(BCC_VERSION) \
	-DENABLE_CLANG_JIT=ON \
	-DENABLE_MAN=OFF

$(eval $(cmake-package))
