// REQUIRES: preload, c_api_execvpe
// RUN: %{compile} '-D_PROGRAM="echo"' -o %t %s
// RUN: %{intercept} --verbose --output %t.sqlite3 -- %t
// RUN: %{events_db} dump --path %t.sqlite3 --output %t.json
// RUN: assert_intercepted %t.json count -eq 2
// RUN: assert_intercepted %t.json contains -program %t -arguments %t
// RUN: assert_intercepted %t.json contains -arguments echo "hi there"

#include "config.h"

#define _GNU_SOURCE

#if defined HAVE_UNISTD_H
#include <unistd.h>
#endif

int main()
{
    char *const program = _PROGRAM;
    char *const argv[] = { _PROGRAM, "hi there", 0 };
    char *const envp[] = { "THIS=THAT", 0 };
    return execvpe(program, argv, envp);
}
