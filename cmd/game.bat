echo off

cls

set "base=src\pax\core\base\export.c"
set "memory=src\pax\core\memory\export.c"
set "string=src\pax\core\string\export.c"
set "format=src\pax\core\format\export.c"
set "stream=src\pax\core\stream\export.c"
set "logging=src\pax\core\logging\export.c"
set "network=src\pax\core\network\export.c"
set "storage=src\pax\core\storage\export.c"
set "console=src\pax\core\console\export.c"
set "structure=src\pax\core\structure\export.c"

set "json=src\pax\encoding\json\export.c"

set "pax=%base% %memory% %string% %format% %stream% %logging% %network% %storage% %console% %structure% %json%"

set "winsock=-lws2_32"

set "lib=%winsock%"
set "dir=src\game\test"
set "src=%pax% src\game\export.c"

zig cc %src% "%dir%\board.c" %lib%   -o board.exe
zig cc %src% "%dir%\message.c" %lib% -o message.exe
