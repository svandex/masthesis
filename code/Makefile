OUTDIR=.\out

all : $(OUTDIR) $(OUTDIR)\ion.exe

$(OUTDIR):
	if not exist "$(OUTDIR)" mkdir $(OUTDIR)

$(OUTDIR)\ionproc.obj : ionproc.cpp
	cl /Zi /nologo /EHsc /c /I. /Ic:\Users\svandex\Documents\GitHub\masthesis\thirdparty\tdmdll\dev\include /Fo:$(OUTDIR)\ionproc.obj /Fd:$(OUTDIR)\ionproc.pdb ionproc.cpp

$(OUTDIR)\ion.obj : ion.cpp
	cl /Zi /nologo /EHsc /c /I. /Ic:\Users\svandex\Documents\GitHub\masthesis\thirdparty\tdmdll\dev\include /Fo:$(OUTDIR)\ion.obj /Fd:$(OUTDIR)\ion.pdb ion.cpp 

$(OUTDIR)\ion.exe : $(OUTDIR)\ion.obj $(OUTDIR)\ionproc.obj
	link /nologo /out:$(OUTDIR)\ion.exe /libpath:c:\Users\svandex\Documents\GitHub\masthesis\thirdparty\tdmdll\dev\lib\64-bit\msvc64 $(OUTDIR)\ion.obj nilibddc.lib user32.lib $(OUTDIR)\ionproc.obj

clean:
	del /F /Q $(OUTDIR)
