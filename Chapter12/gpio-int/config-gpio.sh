#!/bin/sh

echo "Configure P9_15 (gpio1_16, aka gpio 48) is input, trigger on falling edge"
echo 48 > /sys/class/gpio/export
echo falling > /sys/class/gpio/gpio48/edge
