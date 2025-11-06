@echo off

set "code_core_dir=.\code\pax\core\impl"
set "code_encoding_dir=.\code\pax\encoding"
set "code_c4_dir=.\code"

set "test_c4_dir=.\test"

set "base=%code_core_dir%\base\export.c"
set "memory=%code_core_dir%\memory\export.c"
set "string=%code_core_dir%\string\export.c"
set "format=%code_core_dir%\format\export.c"
set "stream=%code_core_dir%\stream\export.c"
set "process=%code_core_dir%\process\export.c"
set "network=%code_core_dir%\network\export.c"
set "storage=%code_core_dir%\storage\export.c"
set "console=%code_core_dir%\console\export.c"
set "time=%code_core_dir%\time\export.c"

set "json=%code_encoding_dir%\json\export.c"

set "game=%code_c4_dir%\game\export.c"
set "server=%code_c4_dir%\server\export.c"

set "test_server=%test_c4_dir%\server\main.c"

set "impl=%base% %memory% %string% %format% %stream% %process% %network% %storage% %console% %time% %json% %game% %server%"

set "lib=-lws2_32"

zig cc --std=c99 %impl% %test_server% %lib% -o server.exe
