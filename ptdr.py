val = "Q}|u`sfg~sf{}|a3"

def xor(v): return "".join([chr(ord(c) ^ v) for c in val])

for i in range(100):
    print(i, xor(i)) 
