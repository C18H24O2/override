#!/usr/bin/env python3

val = "Q}|u`sfg~sf{}|a3"
target = "Congratulations!"

def xor(v): return "".join([chr(ord(c) ^ v) for c in val])

for i in range(100):
    v = xor(i)
    if v == target:
        print(i, xor(i)) 
        print(0x1337d00d - i)
