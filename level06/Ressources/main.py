import sys

argv = sys.argv
if len(argv) != 2:
    s = "thomas"
else:
    s = argv[1]
    l = len(s)
    if l < 6 or l > 31:
        exit(print("Login must be between 6 and 31 characters long"))
    for i in s:
        c = ord(i)
        if c < 32 or c > 126:
            exit(print("Login must only include printable characters"))

var = (ord(s[3]) ^ 4919) + 6221293
for i in s:
    var += (var ^ ord(i)) % 1337
print(var)
