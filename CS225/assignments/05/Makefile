GCC=g++
BCC=bcc32
MSC=cl
GCCFLAGS=-Wall -Wextra -ansi -pedantic
BCCFLAGS=-w
MSCFLAGS=/EHa /MDd /W4 /Za /Zc:forScope /nologo /Wp64  /D_CRT_SECURE_NO_DEPRECATE
OBJECTS0= printjob.cpp print_queue.cpp
DRIVER0=driver.cpp

gcc0:
	$(GCC) -o gcc0.exe $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) 
msc0:                      
	$(MSC) -Femsc0.exe $(DRIVER0) $(OBJECTS0) $(MSCFLAGS) 
bcc0:                     
	$(BCC) -ebcc0.exe $(DRIVER0) $(OBJECTS0) $(BCCFLAGS) 
bcc_cg:
	$(BCC) -ebcc_cg.exe -v -vG $(DRIVER0) $(OBJECTS0) $(BCCFLAGS) 
clean:
	rm -f *.exe *.tds *.o *.obj *manifest*
example:
	g++ driver-example.cpp -o example.exe
