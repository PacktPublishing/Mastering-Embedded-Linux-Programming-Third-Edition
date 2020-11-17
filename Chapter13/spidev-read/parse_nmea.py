#!/usr/bin/env python3

import sys
import pynmea2

for line in sys.stdin:
    try:
        msg = pynmea2.parse(line)
        print(repr(msg))
    except pynmea2.ParseError as e:
        print('Parse error: {}'.format(e))
        continue
