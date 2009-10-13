#!/usr/bin/env python

import math

# Lazy and using this as a global. This might not actually be a good idea.
radius = 1.0

def height(base, hypotenuse):
	return(math.sqrt(hypotenuse**2 - base**2))

def circle_pi(rectangles):
	sum = 0.0
	width = radius/rectangles
	for i in range(rectangles):
		sum += width * height(((0.5+i) * width), radius)

	return(4*sum)

def leibniz_pi(iterations):
	sum = 0
	denominator = 1
	for i in range(iterations):
		if ((denominator//2) %2) == 0:
			sum += 1.0/denominator
		else:
			sum += -1.0/denominator
		denominator += 2

	return(4*sum)

# Function definitions done, now for the program itself.

print("Approximations for pi")
print("Iterations      Circle Method   Leibniz Method")
print("----------------------------------------------")

i = 1
while i <= 1000000:
	print("%(index)10d%(circle_result)20.12f%(leibniz_result)16.12f" % \
		{"index": i, \
		"circle_result": circle_pi(i), \
		"leibniz_result": leibniz_pi(i)})
	i*= 10


