/*

   Define input standard format for a rectangle in the order :
        (top, bottom, right, left)

 */

#ifndef Configurations
#define Configurations

#define MAX_NUMBER_OF_RECTANGLES 10


#define MPW_LT 0
#define MPW_RT 800
#define MPW_BOT 0
#define MPW_TOP 600

#define RECT_NAME_CHARS 5
#define RECT_MIN_NAME_CHAR 'A'
#define RECT_MAX_NAME_CHAR 'Z'

#define MAX_RECTS 200

// For Program

#include <stdio.h>
#include <stdlib.h>


#define MALLOC_ERROR {printf("MALLOC ERROR"); exit(-1);};


#endif
