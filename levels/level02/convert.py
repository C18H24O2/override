import sys
d=[x.strip() for x in sys.stdin.read().strip().split()]
c=[[chr(int(x,16)) for x in [a[i:i+2] for i in range(0,len(a),2)][::-1]] for a in d]
print(''.join([''.join(x) for x in c]))
