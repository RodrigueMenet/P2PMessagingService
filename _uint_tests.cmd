set BUILDIR=.\x64\Debug
set SERVERUTs=%BUILDIR%\P2PService.Tests.exe
set CLIENTUTs=%BUILDIR%\P2PUIClient.Tests.exe

call %SERVERUTs%
call %CLIENTUTs%
pause
