#include <stdio.h>

#include "Lib/IO/IO.h"
#include "Lib/Operations/Operations.h"


int main() {


    Initialize();

    showMenu();

    function *f = NULL;

    //while handler function can run (not null)
    while((f = getFunctionToRun(getResponse()))!=NULL) f();

    return 0;
}
