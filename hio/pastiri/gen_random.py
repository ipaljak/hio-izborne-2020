import random
import sys

n = int(sys.argv[1])
k = int(sys.argv[2])

color, edges, black = [0], [], []

for i in range(2, n + 1):
    p = random.randint(1, i - 1)
    edges.append([p, i])
    color.append(1 - color[p - 1])
    if color[-1]: black.append(i)

k = min(k, len(black))

print(n, k)
for e in edges: print(*e)
print(*random.choices(black, k=k))
