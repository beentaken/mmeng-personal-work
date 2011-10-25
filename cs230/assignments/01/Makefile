# Test stuff.

BINDIR=./build
SOURCES=driver.c gamestatemanager.c input.c level1.c level2.c log.c system.c
#OBJECTS=$(SOURCES:.c=.obj)
OBJECTS:=$(patsubst %.c,$(BINDIR)/%.obj,$(SOURCES))

OUTPUT=assignment.exe

#CC=gcc
#CXX=g++

#OUTFLAG=-o

#CCFLAGS=-D_MBCS -D_WIN32_WINNT=0x0501 -I../include -I./include -I"C:\Program Files\Microsoft DirectX SDK (August 2009)\Include"
#LDFLAGS=-lfmodex_vc -ldxguid -ldinput8 -lwinmm

CC=cl
CXX=cl
LINKER="C:/Program Files/Microsoft Visual Studio 9.0/VC/bin/link.exe"

OUTFLAG=-Fe
LINKOUTFLAG=/out

# In theory, we want these flags.
#CCFLAGS=-nologo -D_MBCS -D_WIN32_WINNT=0x0501 -I../include -I./include -I"C:\Program Files\Microsoft DirectX SDK (August 2009)\Include" -ZI -MDd -c

# Full MSVS-like debug flags.
#CCFLAGS=-nologo -Od -RTC1 -EHsc -W4 -WX -D_MBCS -wd4996 -D_WIN32_WINNT=0x0501 -I../include -I./include -I"C:\Program Files\Microsoft DirectX SDK (August 2009)\Include" -ZI -MDd -c

# Minimum debug flags to make things like, run.
#CCFLAGS=-nologo -W4 -WX -D_MBCS -wd4996 -D_WIN32_WINNT=0x0501 -I../include -I./include -I"C:\Program Files\Microsoft DirectX SDK (August 2009)\Include" -ZI -MDd -c
CCFLAGS=/Od /DWIN32 /D_CRT_SECURE_NO_WARNINGS /W3 /nologo /c /ZI /TP

# MSVS-style link list. A lot of unnecessary stuff.
# LIBRARIES=fmodex_vc.lib dxguid.lib dinput8.lib winmm.lib mykernel32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

# Bare minimum link list.
#LIBRARIES=dxguid.lib dinput8.lib mykernel32.lib winmm.lib user32.lib
LIBRARIES=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib

LDFLAGS=/nologo /DEBUG /LIBPATH:"C:\Program Files\Microsoft Visual Studio 8\VC\lib" /LIBPATH:".\library" /LIBPATH:"C:\Program Files\Microsoft DirectX SDK (August 2009)\Lib\x86" $(LIBRARIES)

all: assignment

assignment: $(OBJECTS)
	$(LINKER) $(LDFLAGS) $(OBJECTS) $(LINKOUTFLAG):"$(BINDIR)\$@.exe"
	cp *.txt $(BINDIR)/

$(BINDIR)/%.obj: %.c
	$(CC) $(CCFLAGS) /Fo${BINDIR}/ $^
#	$(CC) $(CCFLAGS) $@

clean:
	rm -rf -- $(OBJECTS) *.exe *.idb *.pdb $(BINDIR)/*
