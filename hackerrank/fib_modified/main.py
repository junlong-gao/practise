a, b, n = map(int, raw_input().split())
for i in range(3, n+1):
    c = b * b + a
    a,b = b,c
print c


