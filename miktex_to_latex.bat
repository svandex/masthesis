:: Called from Notepad++ Run  
:: [path_to_bat_file] "$(CURRENT_DIRECTORY)" "$(NAME_PART)"  

:: Change Drive and  to File Directory  
%~d1  
cd %1

:: Run Cleanup  
call:cleanup  

:: Run pdflatex -&gt; bibtex -&gt; pdflatex -&gt; pdflatex  
pdflatex %2.tex  
gbk2uni %2.out
bibtex  %2.tex  
:: If you are using multibib the following will run bibtex on all aux files  
:: FOR /R . %%G IN (*.aux) DO bibtex %%G  
pdflatex %2.tex  

:: Run Cleanup  
call:cleanup  

:: Open PDF  
START "" "C:\Program Files (x86)\Foxit Software\Foxit Reader\FoxitReader.exe" %2.pdf -reuse-instance  

:: Cleanup Function  
:cleanup  
del *.dvi
del *.out
del *.log 
del *.aux  
del *.bbl    
del *.blg  
del *.brf  

goto:eof  