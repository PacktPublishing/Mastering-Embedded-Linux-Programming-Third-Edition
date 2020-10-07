#!/bin/sh
# List shared libraries that a program is linked to
#  Chris Simmonds, chris@2net.co.uk

if [ $# != 1 ]; then
    echo "Usage: $0 [progam file]"
    exit 1
fi
${CROSS_COMPILE}readelf -a $1 | grep "program interpreter"
${CROSS_COMPILE}readelf -a $1 | grep "Shared library"
exit 0

