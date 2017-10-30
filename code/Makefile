OUTDIR=.\bin
CLFLAGS=/Zi /nologo /EHsc /c /I. /I..\thirdparty\tdmdll\dev\include /std:c++14

!IFDEF DEBUG
CLFLAGS=/Zi /nologo /EHsc /c /I. /I..\thirdparty\tdmdll\dev\include /DDEBUG /std:c++14
!ENDIF

all : $(OUTDIR) $(OUTDIR)\ion.exe

$(OUTDIR):
	if not exist "$(OUTDIR)" mkdir $(OUTDIR)

$(OUTDIR)\ionproc.obj : ionproc.cpp
	cl $(CLFLAGS) /Fo:$(OUTDIR)\ionproc.obj /Fd:$(OUTDIR)\ionproc.pdb ionproc.cpp

$(OUTDIR)\ion.obj : ion.cpp
	cl $(CLFLAGS) /Fo:$(OUTDIR)\ion.obj /Fd:$(OUTDIR)\ion.pdb ion.cpp 

$(OUTDIR)\ion.exe : $(OUTDIR)\ion.obj $(OUTDIR)\ionproc.obj
	link /nologo /out:$(OUTDIR)\ion.exe /libpath:c:\Users\svandex\Documents\GitHub\masthesis\thirdparty\tdmdll\dev\lib\64-bit\msvc64 $(OUTDIR)\ion.obj nilibddc.lib user32.lib $(OUTDIR)\ionproc.obj

clean:
	del /F /Q $(OUTDIR)
