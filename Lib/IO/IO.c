/*
  IO
  IO also stands for Input/Output, as its name suggests, this library
  contains functions that allow the program to interact with user, and
  vice versa.
  This library forms an interface between user and the computer.
*/

#include <stdio.h>
#include "IO.h"

/*
  void showMenu();
  This function is responsible for showing available
  options on the screen.
  
*/

static inline void clearScreen() {
    // This function was causing problem due to platform dependence
    // GCC is a compiler for Unix / Linux, where as MSVC is for Windows.
    // some functions worked on gcc, while some didnt on MSVC, and vice vera, so we got rid of this for now.
    // The previous version of this function worked in AO3 and older assignments, we don't know if they are broke.
    // The regex being used here stopped working in an expected manner since Windows 11.
    // So we will keep this here. Don't worry about performance, the compiler is smart enough to not call
    // a dummy function.
}

void showMenu() {

    clearScreen();

    // Printing the options.
    printf("Rectangle Program Menu Options\n"
           "==========================\n"
           "1.  Insert User Rectangle\n"
           "2.  Insert Random Rectangle\n"
           "3.  Find Rectangle\n"
           "4.  Delete Rectangle\n"
           "5.  Find Union of Two Rectangles/Intersections Statistics\n"
           "6.  Output Rectangles\n"
           "7.  Output Union/Intersections Statistics\n"
           "8.  Quit"
    );
}

/*
  int getResponse();
  This function is responsible for prompting user to
  enter values for the fraction.
  Prompts user again and again until user enters a 
  valid fraction.
*/

int getResponse() {


    int choice;

    // Displaying Question
    printf("\nPlease choose an option:\n>");

    // Getting Input
    scanf("%i", &choice);

    // Clearing Buffer
    fflush(stdin);

    // Returning the option.
    return choice;
}

/*
  void ClearConsole();
  This function clears the entire console.
  And displays the menu options again.
*/

void ClearConsole() {

    clearScreen();

    fflush(stdin);

    showMenu();
}