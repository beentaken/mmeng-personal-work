# CS180 assignment 1.

all: mandelbrot

mandelbrot: mandelbrot.cpp render_object
	cl /EHsc mandelbrot.cpp render_point.cpp user32.lib gdi32.lib

render_object: render_point.h render_point.cpp
	cl /W4 /c render_point.cpp

clean:
	rm *.obj *.exe

