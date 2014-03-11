@echo off
setlocal

call BuildCurrentBranch.bat

del ..\BinariesX86\Release\*.pdb
del ..\BinariesX64\Release\*.pdb

copy Instructions.txt ..\BinariesX86\Release\Instructions.txt
copy Instructions.txt ..\BinariesX64\Release\Instructions.txt
copy ..\MITLicense.txt ..\BinariesX86\Release\MITLicense.txt
copy ..\MITLicense.txt ..\BinariesX64\Release\MITLicense.txt

set /P _version=Enter version || set _version=NONE
if "%_version%"=="NONE" goto :error

set _versionX86="XInputDotNet-x86-%_version%"
set _versionX64="XInputDotNet-x64-%_version%"

move ..\BinariesX86\Release "%_versionX86%"
move ..\BinariesX64\Release "%_versionX64%"

Zip\zip.exe -r "%_versionX86%.zip" "%_versionX86%"
Zip\zip.exe -r "%_versionX64%.zip" "%_versionX64%"

del /S /Q "%_versionX86%"
del /S /Q "%_versionX64%"
rd /S /Q "%_versionX86%"
rd /S /Q "%_versionX64%"

goto :eof

:error
echo Version required
goto :eof
