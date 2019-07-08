#ifndef __DEBUG
#define __DEBUG

#include    <stdio.h>
#include    <printColor.c> 

int __debug=0;
void printf_d(char *s){
    if (__debug)
        printf("%s\n", s);
}

void debug_on(){
    setColor(PRINT_YELLOW);
    printf("[MODALITA' DEBUG: ON]\n");
    resetColor();
    __debug=1;
}

void debug_off(){
    setColor(PRINT_YELLOW);
    printf("[MODALITA' DEBUG: OFF]\n");
    resetColor();
    __debug=0;
}

int debug() { return __debug; }

#endif
