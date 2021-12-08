#include <stdio.h>
#include "FileWriter.h"

#define FILE_PATH   "../Out/rectangletxt.txt"
#define ACCESS_MODE "w"


// Our output file
static FILE *restrict OutputFile = NULL;
static int FileOpen = 0;

static void Open() {
    if (FileOpen) return;
    FileOpen = 1;
    OutputFile = fopen(FILE_PATH, ACCESS_MODE);
}

static void Close() {
    if (!FileOpen) return;
    FileOpen = 0;
    fclose(OutputFile);
}

static void write(const char *restrict s) {
    fprintf(OutputFile, "%s", s);
}

static void writeLine(const char *restrict s) {
    fprintf(OutputFile, "%s\n", s);
}

const static fileWriter fw = {
        &Open,
        &Close,
        &write,
        &writeLine
};

const fileWriter *restrict FileWriter = &fw;

