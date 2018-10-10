#!/usr/bin/env python

import numpy as np
import imageio


def julia_grid(c_a, c_b, width, height, max_iterations=100):
    """Generates a numpy array of ints out of 255, representing iterations until explosion"""
    c = complex(c_a, c_b)
    xscale = 3 / width
    yscale = xscale

    grid = np.zeros((width, height))
    for a in range(width):
        for b in range(height):
            z = complex(-xscale * width / 2 + a * xscale,
                        -yscale * height / 2 + b * yscale)

            iterations = 0
            while abs(z) <= xscale * width * 10 and iterations < max_iterations:
                z = z**2 + c
                iterations += 1

            grid[a, b] = iterations / max_iterations * 255

    #grid = grid.repeat(4,axis=0).repeat(4,axis=1)
    return grid


def create_gif(width=800, height=800):
    julias = []
    for c_a in (x/5 for x in range(-7,2)):
        row = []
        for c_b in (x/5 for x in range(-1,8)):
            row.append(julia_grid(c_a, c_b, width, height))
            print(f"calculated julia set with c = {c_a}, {c_b}")
        julias.extend(row)
        julias.extend(row[::-1])

    julias.extend(julias[::-1])

    imageio.mimwrite('julia.gif', julias, duration=0.0001)


if __name__ == "__main__":
    create_gif()
