import random
import sys

n = int(sys.argv[1])
k = int(sys.argv[2])

print(n, k)

for i in range(2, n + 1):
    print(random.randint(1, i - 1), i)

print(*random.choices(range(1, n + 1), k=k))
