require 'mkmf'

$CFLAGS << ' -Wall -Werror -Wno-declaration-after-statement '
$CFLAGS << ' --std=c99 -march=native -mtune=native -O2 '
create_makefile 'lexer'
