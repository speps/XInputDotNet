@echo off
setlocal

call BuildCurrentBranch.bat

if not exist ..\XInputUnity\Assets\Plugins\x86 md ..\XInputUnity\Assets\Plugins\x86
if not exist ..\XInputUnity\Assets\Plugins\x86_64 md ..\XInputUnity\Assets\Plugins\x86_64

copy ..\BinariesX86\Release\XInputInterface.dll ..\XInputUnity\Assets\Plugins\x86\
copy ..\BinariesX86\Release\XInputInterface.dll ..\XInputUnity\
copy ..\BinariesX86\Release\XInputDotNetPure.dll ..\XInputUnity\Assets\Plugins\x86\

copy ..\BinariesX64\Release\XInputInterface.dll ..\XInputUnity\Assets\Plugins\x86_64\
copy ..\BinariesX64\Release\XInputDotNetPure.dll ..\XInputUnity\Assets\Plugins\x86_64\
