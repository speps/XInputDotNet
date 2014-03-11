@echo off
setlocal

call UpdateUnityProject.bat

copy ..\MITLicense.txt ..\XInputUnity\Assets\XInputDotNet\

set /P _version=Enter version || set _version=NONE
if "%_version%"=="NONE" goto :error

set _version=XInputDotNet-%_version%.unityPackage
set _projectPath=%~dp0..\XInputUnity

"C:\Program Files (x86)\Unity\Editor\Unity.exe" -batchmode -projectPath "%_projectPath%" -exportPackage "Assets\Plugins" "Assets\XInputDotNet" "..\Build\%_version%" -quit

goto :eof

:error
echo Version required
goto :eof
