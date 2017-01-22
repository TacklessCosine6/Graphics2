@echo off
start egpfw_win_install.bat
set sln=%1
set slndir=%2
set version=%3
cd "%EGPFW_DIR%project\%version%\%slndir%\%sln%"
start devenv "%sln%.sln"
exit