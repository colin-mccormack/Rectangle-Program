#ifndef RECTANGLE
#define RECTANGLE

#include "../../Configurations.h"

typedef struct {
    int left;
    int right;
    int top;
    int bottom;
    char name[RECT_NAME_CHARS + 1];
} Rectangle;

typedef struct {

    Rectangle *__restrict (*const new)();

    void (*const Delete)(const Rectangle *__restrict);

    void (*const Store)(const Rectangle *__restrict);

    int (*const  Contains) (const char *__restrict name);


    Rectangle *__restrict (*const get)(int Index);

    void (*const forEach)(
            const Rectangle *__restrict,
            void(*f)(int index, int left, int right, int top, int bottom, const char *__restrict name));



} rectangleClass;


#endif
