echo off

cls

set "base=src\cpax\pax\base\export.c"
set "memory=src\cpax\pax\memory\export.c"
set "string=src\cpax\pax\string\export.c"
set "format=src\cpax\pax\format\export.c"
set "stream=src\cpax\pax\stream\export.c"
set "json=src\cpax\pax\json\export.c"
set "network=src\cpax\pax\network\export.c"
set "structure=src\cpax\pax\structure\export.c"

set "pax=%base% %memory% %string% %format% %stream% %json% %network% %structure%"

set "winsock=-lws2_32"

set "server=src\message\export.c src\game\export.c src\server\export.c"

set "lib=%winsock%"
set "src=%pax% %server%"
set "dir=src\server\test"

zig cc %src% "%dir%\c4_server.c" %lib% -o c4_server.exe
