echo off

call test\clean.bat

call test\engine\build.bat
call test\server\build.bat
call test\client\build.bat
