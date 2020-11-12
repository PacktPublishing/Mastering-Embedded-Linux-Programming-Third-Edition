#!/bin/bash
# Enable /dev/spidev0.0 on BeagelBone Black

config-pin p9.17 spi_cs
config-pin p9.21 spi
config-pin p9.18 spi
config-pin p9.22 spi_sclk

