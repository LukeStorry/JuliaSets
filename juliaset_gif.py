#!/usr/bin/env python

import numpy as np
import imageio
import time

def julia_grid(c_a, c_b, width, height, max_iterations=50):
    """Generates a numpy array of ints out of 255, representing iterations until explosion"""
    c = complex(c_a, c_b)
    xscale = 4 / width
    yscale = xscale

    grid = np.zeros((height, width))
    for a in range(width):
        for b in range(height):
            z = complex(-xscale * width / 2 + a * xscale,
                        -yscale * height / 2 + b * yscale)

            iterations = 0
            while abs(z) <= xscale * width  and iterations < max_iterations:
                z = z**2 + c
                iterations += 1

            grid[b, a] = iterations / max_iterations * 255

    #grid = grid.repeat(4,axis=0).repeat(4,axis=1)
    return grid


def create_gif(width=1200, height=1000):
    julias = []
    forwards = True

    for c_b in (x/5 for x in range(-5,5)):
        row = []
        for c_a in (x/5 for x in range(-5,5)):
            row.append(julia_grid(c_a, c_b, width, height))
            print(f"calculated julia set with c = {c_a}, {c_b}")

        if forwards:
            julias.extend(row)
        else:
            julias.extend(row[::-1])
        forwards = not forwards
    julias.extend(julias[::-1])

    imageio.mimwrite('julia.gif', julias, duration=0.2)


if __name__ == "__main__":
    start = time.time()
    create_gif()
    print(f"Time Taken:{time.time()-start}")
