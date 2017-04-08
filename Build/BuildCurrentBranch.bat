@echo off
setlocal

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsMSBuildCmd.bat"

MSBuild.exe ..\XInputDotNetPure.sln /t:Clean /p:Configuration=Release /p:Platform=x86
MSBuild.exe ..\XInputDotNetPure.sln /t:Clean /p:Configuration=Release /p:Platform=x64

MSBuild.exe ..\XInputDotNetPure.sln /t:Build /p:Configuration=Release /p:Platform=x86
MSBuild.exe ..\XInputInterface\XInputInterface.vcxproj /t:Build /p:Configuration=Release /p:Platform=Win32

MSBuild.exe ..\XInputDotNetPure.sln /t:Build /p:Configuration=Release /p:Platform=x64
