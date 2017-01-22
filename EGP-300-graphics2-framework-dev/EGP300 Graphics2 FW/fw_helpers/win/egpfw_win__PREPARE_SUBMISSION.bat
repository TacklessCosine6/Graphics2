::Utility script to help you prepare a clean project 
::directory for ALL SUBMISSIONS.
::By Dan Buckstein
@echo off
cd "%~dp0"
echo Preparing submission...
set /p outputdir=" Please type output folder name: "
set outputpath=%outputdir%\egpfw
set rootpath=..\..\..\..
mkdir %outputpath%
cd %outputpath%

::build directory tree
::DO NOT ADD TO THIS LIST
set includedst=include
set resourcedst=resource
set sourcedst=source
set projectdst=project\VS2015
mkdir %includedst%
mkdir %resourcedst%
mkdir %sourcedst%\egpfw
mkdir %sourcedst%\egpfwDemoFreeglut
mkdir %projectdst%\_SLN\EGP-Graphics-FW
mkdir %projectdst%\egpfw
mkdir %projectdst%\egpfwDemoFreeglut

::COPY RELEVANT FILES ONLY
::DO NOT ADD TO THIS LIST
set includedir=%rootpath%\%includedst%
set resourcedir=%rootpath%\%resourcedst%
set sourcedir=%rootpath%\%sourcedst%
set projectdir=%rootpath%\%projectdst%
xcopy /y /s %includedir% 							.\%includedst%\
xcopy /y /s %resourcedir% 							.\%resourcedst%\
xcopy /y /s %sourcedir%\egpfw\*						.\%sourcedst%\egpfw\
xcopy /y /s %sourcedir%\egpfwDemoFreeglut\*			.\%sourcedst%\egpfwDemoFreeglut\
xcopy /y /s %projectdir%\_SLN\EGP-Graphics-FW\*.sln	.\%projectdst%\_SLN\EGP-Graphics-FW\
xcopy /y /s %projectdir%\egpfw\*.vcx* 				.\%projectdst%\egpfw\
xcopy /y /s %projectdir%\egpfwDemoFreeglut\*.vcx* 	.\%projectdst%\egpfwDemoFreeglut\

::done
pause