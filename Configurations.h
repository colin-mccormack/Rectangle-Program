/*

   Configuration.h

   Just a container header file for storing all our configurations.

   This container header file's macros will be used all over the program,
   so if any changes are made here, all files will be automatically updated.

 */

#ifndef Configurations
#define Configurations


#define MPW_LT 0
#define MPW_RT 800
#define MPW_BOT 0
#define MPW_TOP 600

#define RECT_NAME_CHARS 5
#define RECT_MIN_NAME_CHAR 'A'
#define RECT_MAX_NAME_CHAR 'Z'

#define MAX_RECTS 200


// For Error Handling Macros
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ERROR {printf("MALLOC ERROR"); exit(-1);};


#endif
