/*
  IO
  IO also stands for Input/Output, as its name suggests, this library
  contains functions that allow the program to interact with user, and
  vice versa.
  This library forms an interface between user and the computer
*/


#ifndef IO
#define IO

#include <stdio.h>


/*

  This function is responsible for showing available
  options on the screen.

*/
void showMenu();

/*

  This function is responsible for prompting user to
  choose and option and input it.
  Returns the calling function the option chosen by
  the user.

*/

int getResponse();

void ClearConsole();

#endif
