@echo off
setlocal
if not exist "C:\Program Files (x86)\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe" goto DUMPBIN2
set DUMPBIN="C:\Program Files (x86)\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe"
set XBOXKRNL="C:\Program Files (x86)\Microsoft Xbox 360 SDK\lib\xbox\xboxkrnl.lib"
set XAPI="C:\Program Files (x86)\Microsoft Xbox 360 SDK\lib\xbox\xapilib.lib"
goto START
:DUMPBIN2
if not exist "C:\Program Files\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe" goto NODUMPBIN
set DUMPBIN="C:\Program Files\Microsoft Xbox 360 SDK\bin\win32\dumpbin.exe"
set XBOXKRNL="C:\Program Files\Microsoft Xbox 360 SDK\lib\xbox\xboxkrnl.lib"
set XAPI="C:\Program Files\Microsoft Xbox 360 SDK\lib\xbox\xapilib.lib"

:START
FOR %%A IN (%*) DO (
	echo dumping %%A
	REM echo %DUMPBIN% /headers /OUT:"%~dp0%%~nA.txt" %%A
	%DUMPBIN% /headers /OUT:"%~dp0%%~nA.txt" %%A
)
echo Done!
goto EXIT

:NODUMPBIN
echo ERROR! could not find sdk dumpbin.exe

:EXIT
endlocal
REM pause
exit
