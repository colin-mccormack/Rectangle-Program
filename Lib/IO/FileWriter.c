#include <stdio.h>
#include <stdlib.h>
#include "FileWriter.h"

/*

    Output File

    Make sure the source code files have Out folder

    rectangletxt.json is our output file.

 */

#define FILE_PATH   "../Out/rectangletxt.json"

// Access mode is "w", in other words, we are just writing into the files that's it.
#define ACCESS_MODE "w"


// Our output file
static FILE *restrict OutputFile = NULL;

// Tracking if our file is open or not/
static int FileOpen = 0;

// To open the file.
static void Open() {
    if (FileOpen) return;
    FileOpen = 1;

    /*


     */

    OutputFile = fopen(FILE_PATH, ACCESS_MODE);

    if (!OutputFile) {
        printf("ERROR OCCURRED IN OPENING FILE!\n");
        exit(-1);
    }
}

// To close it
static void Close() {
    if (!FileOpen) return;
    FileOpen = 0;
    fclose(OutputFile);
}

// To write into the file
static void write(const char *restrict s) {
    fprintf(OutputFile, "%s", s);
}

// To write into the file again
static void writeLine(const char *restrict s) {
    fprintf(OutputFile, "%s\n", s);
}

/*

    This is controversial, but doesnt matter

    We are just creating a class for encapsulating all
    our functions.

 */
const static fileWriter fw = {
        &Open,
        &Close,
        &write,
        &writeLine
};

const fileWriter *restrict FileWriter = &fw;

