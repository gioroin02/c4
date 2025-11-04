echo off

call test\clean.bat

call test\game\build.bat
call test\server\build.bat
call test\client\build.bat
