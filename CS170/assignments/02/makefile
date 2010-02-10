# Macros ========================================

# Change compiler path to match your system
CC=g++
CFLAGS=-Wall -Wextra -ansi -pedantic
OBJECTS=driver-sample.obj PRNG.obj Ocean.obj
EXEFILE=WarBoats
ERASE=rm

# Targets ========================================

$(EXEFILE) : $(OBJECTS)
	$(CC) -o WarBoats $(OBJECTS)

driver-sample.obj : driver-sample.cpp WarBoats.h PRNG.h
	$(CC) -c -o driver-sample.obj $(CFLAGS) driver-sample.cpp

Ocean.obj : Ocean.cpp Ocean.h WarBoats.h
	$(CC) -c -o Ocean.obj $(CFLAGS) Ocean.cpp

PRNG.obj : PRNG.cpp PRNG.h
	$(CC) -c -o PRNG.obj $(CFLAGS) PRNG.cpp

all : 
	$(MAKE) $(EXEFILE)

rebuild : 
	$(MAKE) clean
	$(MAKE) all

clean :
	rm $(EXEFILE) $(OBJECTS)
