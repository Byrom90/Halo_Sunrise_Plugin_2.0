@echo off
setlocal
if not exist "C:\Program Files (x86)\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe" goto DUMPBIN2
set DUMPBIN="C:\Program Files (x86)\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe"
set XBOXKRNL="C:\Program Files (x86)\Microsoft Xbox 360 SDK\lib\xbox\xboxkrnl.lib"
set XAPI="C:\Program Files (x86)\Microsoft Xbox 360 SDK\lib\xbox\xapilib.lib"
set XAV="C:\Program Files (x86)\Microsoft Xbox 360 SDK\lib\xbox\xav.lib"
goto START
:DUMPBIN2
if not exist "C:\Program Files\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe" goto NODUMPBIN
set DUMPBIN="C:\Program Files\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe"
set XBOXKRNL="C:\Program Files\Microsoft Xbox 360 SDK\lib\xbox\xboxkrnl.lib"
set XAPI="C:\Program Files\Microsoft Xbox 360 SDK\lib\xbox\xapilib.lib"
set XAV="C:\Program Files\Microsoft Xbox 360 SDK\lib\xbox\xav.lib"

:START
if not exist "%~1" goto NOFILE
echo dumping "%~1"
echo .
echo %DUMPBIN% /headers /OUT:"%~dp0%~n1.txt" "%~1"
%DUMPBIN% /headers /OUT:"%~dp0%~n1.txt" "%~1"
echo Done!
goto EXIT

:NOFILE
echo arguement not supplied, dumping xboxkrnl.lib and xapi.lib headers
echo.
if not exist %XAPI% goto NOXAPI
echo %DUMPBIN% /headers /OUT:"%~dp0xapi_xam.txt" %XAPI%
%DUMPBIN% /headers /OUT:"%~dp0xapi_xam.txt" %XAPI%
echo.
echo.
:NOXAPI
if not exist %XBOXKRNL% goto NOKRNL
echo %DUMPBIN% /headers /OUT:"%~dp0xboxkrnl.txt" %XBOXKRNL%
%DUMPBIN% /headers /OUT:"%~dp0xboxkrnl.txt" %XBOXKRNL%
echo.
echo.
:NOKRNL
if not exist %XAV% goto NOKRNL
echo %DUMPBIN% /headers /OUT:"%~dp0xav_xam.txt" %XAV%
%DUMPBIN% /headers /OUT:"%~dp0xav_xam.txt" %XAV%

:NOXAV
echo Done!
goto EXIT

:NODUMPBIN
echo ERROR! could not find sdk dumpbin.exe

:EXIT
echo.
echo.
endlocal
REM pause
REM exit
