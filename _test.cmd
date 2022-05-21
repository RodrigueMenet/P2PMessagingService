set BUILDIR=.\x64\Debug
set SERVEREXE=%BUILDIR%\P2PService.exe
set CLIENTEXE=%BUILDIR%\P2PUIClient.exe

start /B "" cmd /c  %CLIENTEXE% 1
start /B "" cmd /c  %CLIENTEXE% 2
start /B "" cmd /c  %CLIENTEXE% 3
start /B "" cmd /c  %CLIENTEXE% 4
start /B "" cmd /c  %CLIENTEXE% 5
start /B "" cmd /c  %SERVEREXE%
