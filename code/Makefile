OUTDIR=.\out

all : $(OUTDIR) $(OUTDIR)\ion.exe

$(OUTDIR):
	if not exist "$(OUTDIR)" mkdir $(OUTDIR)

$(OUTDIR)\ion.obj : ionproc.cpp
	cl /Zi /nologo /EHsc /c /Ic:\Users\svandex\Documents\GitHub\masthesis\thirdparty\tdmdll\dev\include /Fo:$(OUTDIR)\ion.obj /Fd:$(OUTDIR)\ion.pdb ionproc.cpp 

$(OUTDIR)\ion.exe : $(OUTDIR)\ion.obj
	link /nologo /out:$(OUTDIR)\ion.exe /libpath:c:\Users\svandex\Documents\GitHub\masthesis\thirdparty\tdmdll\dev\lib\64-bit\msvc64 $(OUTDIR)\ion.obj nilibddc.lib user32.lib
