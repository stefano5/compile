#ifndef __MANAGEMENT_STRING
#define __MANAGEMENT_STRING

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <pwd.h>
#include    <assert.h>
#include    <debug.c>

#define FFLUSH while(getchar()!='\n') ;

char *ltrim(char *s){
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s){
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s){
    return rtrim(ltrim(s)); 
}

void readString(char s[], int dim){
    int i = 0;
    for (i = 0; i<dim - 1; i++)
        if ((s[i] = getchar()) == '\n') break;
    if (i == dim - 1) FFLUSH;
    s[i] = '\0';
}

void initArray_str(char *array, int dim) {
    for (int i=0; i<dim; i++) {
        array[i] = '\0';
    }
}

int subString(char *str, int start, int end) {
    int len = strlen(str);
    if (end<0) end=len;
    if (start<0) start=0;
    if (end>len) {
        if (debug()){
            printf("[%s->subString] Nothing to do. String %s have dim:%d, so the index %d (end index) don't exist\n", __FILE__, str, len, end, end);
        } 
        return -1;
    }
    if (start > len || start > end) {
        printf("[%s->subString] Error substring (size). str:%s--start:%d--end:%d--lenstr:%d\n", __FILE__, str, start, end, len);
        return -1;
    }
    char *str_temp = (char*)malloc(sizeof(char) * len);    //of course, sizeof(char) = 1, but to leggibility...
    int new_index=0;
    for (int i=0;i<len; i++ ){
        if(i>=start && i<end){
            str_temp[new_index++]=str[i];
        }
    }
    str_temp[new_index]='\0';
    strcpy(str, str_temp);
    free(str_temp);
    return new_index;
}



void _lowerCase(char *str) {
    //todo
}

void _upperCaseFirstChar(char *str) {
    //todo
}

char** str_split(char* a_str, const char a_delim) {
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    while (*tmp) {
        if (a_delim == *tmp) {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    // Add space for trailing token
    count += last_comma < (a_str + strlen(a_str) - 1);

    // Add space for terminating null string so caller knows where the list of returned strings ends.
    count++;

    result = (char**)malloc(sizeof(char*) * count);

    if (result) {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token) {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}


#endif
