#include <stdio.h>

#include "LIb/IO/FileWriter.h"

int main() {


    Initialize();

    showMenu();



    function *f = NULL;

    while((f = getFunctionToRun(getResponse()))!=NULL) f();


    return 0;
}
