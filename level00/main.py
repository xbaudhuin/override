import sys

argv = sys.argv
args = argv[1] + argv[2] + argv[3] + argv[4] + argv[5]

s = b''
for i in range(0, len(args), 2):
    s += bytes(hex(args[i:i+1]))
print(s)
