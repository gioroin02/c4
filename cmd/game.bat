echo off

cls

set "base=src\cpax\pax\base\export.c"
set "memory=src\cpax\pax\memory\export.c"
set "string=src\cpax\pax\string\export.c"
set "format=src\cpax\pax\format\export.c"
set "stream=src\cpax\pax\stream\export.c"
set "network=src\cpax\pax\network\export.c"
set "structure=src\cpax\pax\structure\export.c"
set "json=src\cpax\pax\json\export.c"

set "pax=%base% %memory% %string% %format% %stream% %network% %structure% %json%"

set "winsock=-lws2_32"

set "lib=%winsock%"
set "dir=src\game\test"
set "src=%pax% src\game\export.c"

zig cc %src% "%dir%\board.c" %lib% -o board.exe
