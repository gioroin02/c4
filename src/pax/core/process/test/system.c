#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    printf("Core amount  = %lli\n", pxProcessCoreAmount());
    printf("Thread ident = %lli\n", pxCurrentThreadIdent());
}
