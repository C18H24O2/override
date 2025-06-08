#!/usr/bin/env python3

import sys
if len(sys.argv) == 1:
    for c in range(26):
        print("".join([chr(ord('a') + c) + chr(i) for i in range(65, 91)]), end='')
else:
    print("A" * int(sys.argv[1]))
    print("B" * int(sys.argv[1]))
