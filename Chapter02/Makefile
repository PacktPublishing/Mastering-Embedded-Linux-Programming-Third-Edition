# Mastering-Embedded-Linux-Programming-Third-Edition/Chapter02/Makefile

# Usage:
#
#     $ export CROSS_COMPILE=~/x-tools/arm-cortex_a8-linux-gnueabihf/bin/arm-cortex_a8-linux-gnueabihf-
#     $ make clean all check
#

CC := $(CROSS_COMPILE)$(CC)
AR := $(CROSS_COMPILE)$(AR)

CFLAGS = -Wall -g -fPIC -Ilibrary/inc

.PHONY: all
all: \
  library/hello-arm/hello-arm-shared \
  library/hello-arm/hello-arm-static

library/hello-arm/hello-arm-shared: LDFLAGS = -Llibrary/shared -ltest
library/hello-arm/hello-arm-shared: LDLIBS = library/shared/libtest.so
library/hello-arm/hello-arm-shared: library/hello-arm/hello-arm.c library/shared/libtest.so
	$(LINK.c) $< $(LOADLIBES) $(LDLIBS) -o $@

library/shared/libtest.so: LDFLAGS = -shared
library/shared/libtest.so: library/shared/testlib.o
	$(LINK.o) -o $@ $^

library/hello-arm/hello-arm-static: LDFLAGS = -static
library/hello-arm/hello-arm-static: LDLIBS = library/static/libtest.a
library/hello-arm/hello-arm-static: library/hello-arm/hello-arm.c library/static/libtest.a
	$(LINK.c) $< $(LOADLIBES) $(LDLIBS) -o $@

library/static/libtest.a: library/static/testlib.o
	$(AR) $(ARFLAGS) $@ $^

.PHONY: check
check: library/hello-arm/hello-arm-shared library/hello-arm/hello-arm-static
	file $^

.PHONY: clean
clean:
	rm -vf \
		library/hello-arm/hello-arm-shared \
		library/hello-arm/hello-arm-static \
		library/hello-arm/hello-arm.o \
		library/shared/libtest.so \
		library/shared/testlib.o \
		library/static/libtest.a \
		library/static/testlib.o
