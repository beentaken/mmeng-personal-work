GCC=g++
BCC=bcc32
MSC=cl
GCCFLAGS=-Wall -Wextra -ansi -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder -Wl,--enable-auto-import
GCCOPTIMIZE=-O3
GCC_COVERAGE_OPTIONS=--coverage -fprofile-arcs -fbranch-probabilities
BCCFLAGS=-w
MSCFLAGS=                 /EHa      /MDd /W4 /Za /Zc:forScope /nologo /D_CRT_SECURE_NO_DEPRECATE
MSCFLAGSOPTIMIZED=/O2 /GL /EHsc /Za /MD  /W4 /Za /Zc:forScope /nologo /D_CRT_SECURE_NO_DEPRECATE /D"_SECURE_SCL 0"
OBJECTS0=array.cpp element1.cpp element2.cpp element-factory.cpp
DRIVER0=driver.cpp
INCLUDE1=-I ../../../common-code/
MSCINCLUDE=/I"../../../common-code/"
MSCDEFINE=
DEFINE=#-DINLINE_MAP

gcc0:
	$(GCC) -o $@.exe $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) -pedantic $(GCCOPTIMIZE) $(INCLUDE1) $(DEFINE)
gcc0_nopedantic:
	$(GCC) -o $@.exe $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) $(GCCOPTIMIZE) $(INCLUDE1) $(DEFINE)
msc0:
	$(MSC) /Fe$@.exe $(DRIVER0) $(OBJECTS0) $(MSCFLAGS) $(MSCINCLUDE)  $(MSCDEFINE)
msc_opt0:
	$(MSC) /Fe$@.exe $(DRIVER0) $(OBJECTS0) $(MSCFLAGSOPTIMIZED) $(MSCINCLUDE)  $(MSCDEFINE) 
bcc0:
	$(BCC) -e$@.exe  $(DRIVER0) $(OBJECTS0) $(BCCFLAGS) $(DEFINE)
bcc_cg:
	$(BCC) -e$@.exe -v -vG $(DRIVER0) $(OBJECTS0) $(BCCFLAGS) $(DEFINE)
gcc_coverage:
	$(GCC) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) $(GCC_COVERAGE_OPTIONS) $(INCLUDE1)  $(DEFINE) -o $@
clean:
	rm -f *gcno *gcda *gcov *.exe *.o *.obj *.tds
