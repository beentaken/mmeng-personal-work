OSTYPE := $(shell uname)
	ifeq ($(OSTYPE),Linux)
	CYGWIN=
	else
	CYGWIN=-Wl,--enable-auto-import
endif
	
bcc_c:
	echo Compile all with C
	bcc32 -c -w -tWC driver.c
	bcc32 -c -w splitter.c
	bcc32 -ebcc0.exe driver.obj splitter.obj

bcc_c_cpp:
	echo Compile with C and C++
	bcc32 -c -w -P -tWC driver.cpp
	bcc32 -c -w splitter.c
	bcc32 -ebcc1.exe driver.obj splitter.obj

bcc_cpp:
	echo Compile all with C++
	bcc32 -c -w -P -tWC driver.cpp
	bcc32 -c -w -P splitter.c
	bcc32 -ebcc2.exe driver.obj splitter.obj

gcc_c:
	echo Compile all with C
	gcc -c splitter.c -Wall -Wextra -ansi -pedantic
	gcc -c driver.c -Wall -Wextra -ansi -pedantic
	gcc -o gcc0.exe splitter.o driver.o -Wall -Wextra -ansi -pedantic

gcc_c_cpp:
	echo Compile with C and C++
	gcc -c splitter.c -Wall -Wextra -ansi -pedantic
	g++ -c driver.cpp -Wall -Wextra  -ansi -pedantic
	g++ -o gcc1.exe splitter.o driver.o $(CYGWIN) -Wall -Wextra  -ansi -pedantic

gcc_cpp:
	echo Compile all with C++
	g++ -c splitter.c -Wall -Wextra -ansi -pedantic
	g++ -c driver.cpp -Wall -Wextra -ansi -pedantic
	g++ -o gcc2.exe splitter.o driver.o $(CYGWIN) -Wall -Wextra -ansi -pedantic

msc_c:
	echo compile all with C
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TC splitter.c /c
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TC driver.c /c
	cl /W4 /Femsc0.exe splitter.obj driver.obj

msc_c_cpp:
	echo compile with C and C++
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TC splitter.c /c
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TP /EHsc driver.cpp /c
	cl /W4 /Femsc1.exe splitter.obj driver.obj

msc_cpp:
	echo compile all with C++
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TP splitter.c /c
	cl /D  "_CRT_SECURE_NO_DEPRECATE" /W4 /Za /TP /EHsc driver.cpp /c
	cl /W4 /Femsc2.exe splitter.obj driver.obj
clean:
	rm -f *.o *.obj *.manifest *.tds *.exe

