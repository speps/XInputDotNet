@echo off
setlocal

call BuildCurrentBranch.bat

call :copyToUnity ..\XInputUnity4
copy ..\BinariesX86\Release\XInputInterface.dll ..\XInputUnity4\

call :copyToUnity ..\XInputUnity5

exit /b 0

:copyToUnity
setlocal
if not exist %1\Assets\XInputDotNet\Plugins\x86 md %1\Assets\XInputDotNet\Plugins\x86
if not exist %1\Assets\XInputDotNet\Plugins\x86_64 md %1\Assets\XInputDotNet\Plugins\x86_64

copy ..\BinariesX86\Release\XInputDotNetPure.dll %1\Assets\XInputDotNet\Plugins\

copy ..\BinariesX86\Release\XInputInterface.dll %1\Assets\XInputDotNet\Plugins\x86\
copy ..\BinariesX64\Release\XInputInterface.dll %1\Assets\XInputDotNet\Plugins\x86_64\
endlocal
