GCC=gcc
BCC=bcc32
MSC=cl
GCCFLAGS=-ansi -Wall -Wextra -pedantic -Wstrict-prototypes -Wmissing-prototypes -Wdeclaration-after-statement
GCCOPTIMIZE=-O3
GCC_COVERAGE_OPTIONS=--coverage -fprofile-arcs -fbranch-probabilities
BCCFLAGS=-w
MSCFLAGS=/MDd /W4 /Za /Zc:forScope /nologo /D_CRT_SECURE_NO_DEPRECATE
MSCOPTIMIZE=/O2 /MD
OBJECTS0=map.c
INCLUDE_EXT=-I ../../../common-code
GCCOPTIMIZE=-O3
DRIVER0=driver.c
#DEFINE=-DINLINE_MAP

gcc0:
	$(GCC) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) $(GCCOPTIMIZE) $(INCLUDE_EXT) $(DEFINE) -o $@.exe
msc0:
	$(MSC) /Fe$@.exe $(DRIVER0) $(OBJECTS0) $(MSCFLAGS) 
bcc0:
	$(BCC) -e$@.exe $(DRIVER0) $(OBJECTS0) $(BCCFLAGS) 
bcc_cg:
	$(BCC) -e$@.exe -v -vG $(DRIVER0) $(OBJECTS0) $(BCCFLAGS) 
clean:
	rm -f *gcno *gcda *gcov *.exe *.o *.obj *.tds
