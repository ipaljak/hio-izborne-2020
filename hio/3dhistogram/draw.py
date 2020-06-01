import numpy as np
import matplotlib.pyplot as plt
import sys

from mpl_toolkits.mplot3d import Axes3D


def main():
    a = []
    b = []
    filename = sys.argv[1]
    try:
        lines = open(filename).readlines()
        for line in lines[1:]:
            aa, bb = map(int, line.split())
            a.append(aa)
            b.append(bb)
    except Exception as e:
        print("Greska!", e)
        raise

    x, y, z = np.indices((len(a), max(b), max(a)))
    bars = []
    for i in range(len(a)):
        bars.append((x >= i) & (x < i + 1) & (y < b[i]) & (z < a[i]))

    c = ['red', 'blue', 'green', 'yellow', 'brown']

    voxels = bars[0]
    for bar in bars[1:]:
        voxels = voxels | bar

    colors = np.empty(voxels.shape, dtype=object)
    for (i, bar) in enumerate(bars):
        colors[bar] = c[i % len(c)]

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.voxels(voxels, facecolors=colors, edgecolor='k')

    plt.show()

if __name__ == "__main__":
    main()
