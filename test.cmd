set BUILDIR=.\x64\Debug
set SERVEREXE=%BUILDIR%\P2PService.exe
set CLIENTEXE=%BUILDIR%\P2PUIClient.exe

start /B "" cmd /c  %SERVEREXE%
start /B "" cmd /c  %CLIENTEXE% 1
start /B "" cmd /c  %CLIENTEXE% 2