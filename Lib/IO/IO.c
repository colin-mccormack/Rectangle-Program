/*
  IO
  IO also stands for Input/Output, as its name suggests, this library
  contains functions that allow the program to interact with user, and
  vice versa.
  This library forms an interface between user and the computer.
*/

#include <stdio.h>
#include <stdlib.h>

#include "IO.h"
/*
  void showMenu();
  This function is responsible for showing available
  options on the screen.
  
*/

void showMenu() {

  //Clearing Console of everything in it.
  //To read more about this check out : https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
  printf("\e[1;1H\e[2J");

  // Printing the options.
  printf("Options:\n");
  printf ("1. Create Random Fraction\n");
  printf ("2. Get Fraction From User\n");
  printf ("3. Display Fractions\n");
  printf ("4. Evaluate Expression\n");
  printf ("5. Display All Equations\n");
  printf ("6. Quit\n");

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
  printf ("\nPlease choose an option:\n>");  

  // Getting Input
  scanf ("%i", &choice);
  
  // Clearing Buffer  
  fflush(stdin);

  // Returing the option.
  return choice;
}

/*
  void ClearConsole();
  This function clears the entire console.
  And displays the menu options again.
*/

void ClearConsole() {

  fflush(stdin);

  showMenu();
}