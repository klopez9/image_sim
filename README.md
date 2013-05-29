image_sim
===============

"Performance-Lab" assignment

This lab assigment was designed to get us (the students) thinking
about code optimization. This program:

----simulates an image using a matrix, where each cell is a "pixel"

----contains the functions:

--------rotate() //flips the matrix 90 degrees clockwise

--------smooth() //averages values of adjacent cells to "smooth" image

We were given all the necessary files and were asked to optimize the
 algorithms in the rotate() and smooth() functions to decrease
 execution time. We were graded based on the average performance for
 rotating/smoothing images of different sizes; i.e. a 64-pixel image,
 128, 256, etc. We were given explanations of concepts like loop
 unrolling, code motion, and blocking, but instead my partner and I
 opted to use pthreads, dividing the matrix into 4 smaller matrices and
 smoothing/rotating them simultaneously. We kept the naive
 implementation for smaller image sizes since we got worse performance
 on those using pthreads.

Used with permission by Binghamton University CS Department (see README
file for original copyright information)
