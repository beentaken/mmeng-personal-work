
all: bounce

bounce: Bounce.cpp DotWindow.cpp Compute.cpp
	cl /W3 /EHsc Bounce.cpp DotWindow.cpp Compute.cpp user32.lib gdi32.lib

clean:
	rm Bounce.exe Bounce.obj Compute.obj DotWindow.obj

