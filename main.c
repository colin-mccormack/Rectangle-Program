#include <stdio.h>

#include "LIb/IO/FileWriter.h"

int main() {

    showMenu();

    UnionRectTesting();
    IntersectRectTesting();

    function *f = NULL;

    while((f = getFunctionToRun(getResponse()))!=NULL) f();


    return 0;
}
