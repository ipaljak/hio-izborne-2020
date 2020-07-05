n = int(input())

if n <= 2:
    s = '10'
elif n <= 4:
    s = '1100'
elif n <= 8:
    s = '11101000'
else:
    s = '110100' * (n // 6 + 1)

print(s[:n])
