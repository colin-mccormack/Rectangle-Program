/*

    Rectangle Program

    This project is divided into multiple files and libraries

    Lib/IO
        - IO.h : Forms and Interface between User and the Program
        - FileWriter.h : Writes contents into Out/rectangles.json

    Lib/LinkedHashMap
        - LinkedHashMap.h: Used to create Linked Hash Map, for information,
                         read the header file

    Lib/Rectangle
        - RectangleClass.h: Used for creating instances for Rectangles and Rectangle Statistics

    Lib/Operations
        - Operations.h: controls the program flow, "Brain" of the program.

    This file: Entry Point of the program

    @authors: Abdul Mannan Syed, asyed24@ocdsb.ca
              Colin McCormack, cmcco3@ocdsb.ca

 */


#include <stdio.h>

#include "Lib/IO/IO.h"
#include "Lib/Operations/Operations.h"


int main() {

    /*

        Initialize()

        called from Operations.h for basic program initialisations
     */

    Initialize();


    // Printing out the options for the user
    showMenu();


    // function corresponds to the type of function we are storing here.
    function *f = NULL;

    /*

        This part is a bit interesting

        (from IO.h) getResponse() returns an integer value that represents the user input.
        (from Operations.h) getFunctionToRun() uses that integer value and returns a pointer to a function
        corresponding to the user input.

        If the user wants to quit, getFunctionToRun() will return NULL

     */

    while ((f = getFunctionToRun(getResponse())) != NULL) f();

    return 0;
}
