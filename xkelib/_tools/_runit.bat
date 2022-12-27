@echo off

call dump_libheader.bat

if not exist xam.def goto NOXAMDEF
call .\deffix.exe xam.def manuals_xam.txt xam.def
call .\deffix.exe xam.def xav_xam.txt xam.def
call .\deffix.exe xam.def xapi_xam.txt xam.def
goto DOKERNEL
:NOXAMDEF
echo.
echo ERROR! xam.def was not found!

:DOKERNEL
if not exist kernel.def goto NOKERNELDEF
call .\deffix.exe kernel.def xboxkrnl.txt kernel.def
goto EXIT

:NOKERNELDEF
echo.
echo ERROR! kernel.def was not found!

:EXIT
if not exist xapi_xam.txt goto NOTXT1
del /f /q xapi_xam.txt
:NOTXT1
if not exist xav_xam.txt goto NOTXT2
del /f /q xav_xam.txt
:NOTXT2
if not exist xboxkrnl.txt goto NOTXT3
del /f /q xboxkrnl.txt
:NOTXT3
echo.
echo.
echo Done!
pause
exit
