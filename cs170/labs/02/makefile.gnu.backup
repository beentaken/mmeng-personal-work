ifndef $(CXX)
	CXX=g++
endif

SRCFILES=main.cpp fibonacci.cpp

ifeq "$(CXX)" "g++"
	CCFLAGS=-Wall -Wextra -Werror -ansi -pedantic
	LDFLAGS=-Wl,--enable-auto-import
	OUTFLAG=-o 
	BINDIR=gnu
else ifeq "$(CXX)" "cl"
	CCFLAGS=/W4 /EHa /Za /WX
	OUTFLAG=/Fe
	BINDIR=microsoft
else ifeq "$(CXX)" "bcc32"
	CCFLAGS=-w
	OUTFLAG=-e
	BINDIR=borland
endif

all: fib

fib:
	$(CXX) $(CCFLAGS) $(LDFLAGS) $(OUTFLAG)$(BINDIR)/$@ $(SRCFILES)

clean:
	rm ./*.obj $(BINDIR)/*

