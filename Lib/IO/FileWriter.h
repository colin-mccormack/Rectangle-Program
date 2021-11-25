#ifndef FILE_WRITER
#define FILE_WRITER

typedef struct {
    void (*const Open)();
    void (*const Close)();
    void (*const write)(const char *restrict s);
    void (*const writeLine)(const char *restrict s);
} fileWriter;


extern const fileWriter* restrict FileWriter;


#endif