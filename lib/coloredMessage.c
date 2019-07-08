#ifndef COLORED_MESSAGE_C
#define COLORED_MESSAGE_C

#include <printColor.c>

void abortMessage(const char *mex) {
    printf("[");
    setColor(PRINT_RED);
    printf("Abort");
    resetColor();
    printf("] %s", mex);
}

void successMessage(const char *mex) {
    printf("[");
    setColor(PRINT_GREEN);
    printf("Success");
    resetColor();
    printf("] %s", mex);
}

void warningMessage(const char *mex) {
    printf("[");
    setColor(PRINT_YELLOW);
    printf("Warning");
    resetColor();
    printf("] %s", mex);
}

#endif
