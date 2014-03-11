@echo off
setlocal

set _msbuildpath=C:\Windows\Microsoft.NET\Framework64\v4.0.30319\MSBuild.exe

"%_msbuildpath%" ..\XInputDotNetPure.sln /t:Clean /p:Configuration=Release /p:Platform=x86
"%_msbuildpath%" ..\XInputDotNetPure.sln /t:Clean /p:Configuration=Release /p:Platform=x64

"%_msbuildpath%" ..\XInputDotNetPure.sln /t:Build /p:Configuration=Release /p:Platform=x86
"%_msbuildpath%" ..\XInputInterface\XInputInterface.vcxproj /t:Build /p:Configuration=Release /p:Platform=Win32

"%_msbuildpath%" ..\XInputDotNetPure.sln /t:Build /p:Configuration=Release /p:Platform=x64
