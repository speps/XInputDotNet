@echo off
setlocal

call UpdateUnityProject.bat

echo "Up-to-date documentation at: https://github.com/speps/XInputDotNet" > ..\XInputUnity5\Assets\XInputDotNet\Docs.txt
copy ..\MITLicense.txt ..\XInputUnity5\Assets\XInputDotNet\

set /P _version=Enter version || set _version=NONE
if "%_version%"=="NONE" goto :error

set _version=XInputDotNet-%_version%.unityPackage
set _projectPath=%~dp0..\XInputUnity5

echo Building package %_version% from %_projectPath%
"C:\Program Files\Unity\Editor\Unity.exe" -batchmode -projectPath "%_projectPath%" -exportPackage "Assets\XInputDotNet" "..\Build\%_version%" -quit

goto :eof

:error
echo Version required
goto :eof
