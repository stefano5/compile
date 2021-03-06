//#define DEBUG             //Per compilare il main
//
//NON PIÙ LINKATA


#if defined(DEBUG) 
    #include <function.h>
#endif

#ifndef COUNT_T
#define COUNT_T

void __calculatesDifferencePrintError(int hStart, int mStart, int hEnd, int mEnd) {
    printf("Inizio (");
    if (hStart > 24) {
        setColor(PRINT_RED);  
        printf("%d", hStart);
        resetColor();
    } else {
        setColor(PRINT_BLUE);  
        printf("%d", hStart);
        resetColor();
    }
    printf(":");
    if (mStart > 60) {
        setColor( PRINT_RED);  
        printf("%d", mStart);
        resetColor();
    } else {
        setColor(PRINT_BLUE);  
        printf("%d", mStart);
        resetColor();
    }

    printf(") Fine: (");

    if (hEnd > 24) {
        setColor(PRINT_RED);  
        printf("%d", hEnd);
        resetColor();
    } else {
        setColor(PRINT_BLUE);  
        printf("%d", hEnd);
        resetColor();
    }
    printf(":");
    if (mEnd > 60) {
        setColor(PRINT_RED);  
        printf("%d", mEnd);
        resetColor();
    } else {
        setColor(PRINT_BLUE);  
        printf("%d", mEnd);
        resetColor();
    }
    printf(")\n");

}

int* calculatesDifference(char *hourStart, char *hourEnd){
    if (strlen(hourStart)<5 || strlen(hourEnd)<5){
        printf("[%s->calculatesDifference] il parametro passato deve avere lunghezza fissa di 6 caratteri. Adesso avrai una violazione in memoria\n", __FILE__);
        printf("Start: >%s< strlen=%d\n", hourStart, (int)strlen(hourStart));
        printf("End: >%s< strlen=%d\n", hourEnd, (int)strlen(hourEnd));
        return NULL;
    }

    int hStart, mStart;
    int hEnd, mEnd;
    char *dump = (char*)malloc(6);

    strcpy(dump, hourStart);
    subString(dump, 0, 2);
    hStart = atoi(dump);

    strcpy(dump, hourStart);
    subString(dump, 3, 5);
    mStart=atoi(dump);

    strcpy(dump, hourEnd);
    subString(dump, 0, 2);
    hEnd=atoi(dump);

    strcpy(dump, hourEnd);
    subString(dump, 3, 5);
    mEnd=atoi(dump);

    free(dump);

    if (debug()) {
        printf("Ora inizio: %d:%d\n", hStart, mStart);
        printf("Ora fine: %d:%d\n", hEnd, mEnd);
    }

    if (hStart > 24 || mStart > 60 || hEnd > 24 || mEnd > 60) {
        printf("[%s->calculatesDifference] Ore passate errate. ", __FILE__);
        __calculatesDifferencePrintError(hStart, mStart, hEnd, mEnd);
        printf("Adesso avrai una violazione in memoria\n");
        return NULL;
    }
    int countH = 0, countM = 0, flag=0;

reCompute:
    if (hStart != hEnd) { 
        while (1) {
            countH++;
            hStart++;
            if (hStart == 24) {
                hStart = 0;
            }

            if (hStart == hEnd){
                break;
            }
        }
    } else {
        if (mStart > mEnd) { 
            printf("Tick\n");
            hStart += 1;
            flag = 1;
            goto reCompute;
        }
    }

    if (flag) countH++;

    if (mStart != mEnd) {
        while (1) {
            countM++;
            mStart++;
            if (mStart == 60) {
                countH--;
                mStart = 0;
            }

            if (mStart == mEnd) {
                break;
            }
        }
    }
    //printf("Res:   %d:%d\n", countH, countM);
    int *ret = (int*)malloc(sizeof(int) * 2);
    ret[0] = countH;
    ret[1] = countM;
    return ret;
}

#ifdef DEBUG
int main(void){
    debug_on();
    printf("ciao\n");
    int *par=calculatesDifference("17:38", "07:27");
    printf("Tempo passato: %d:%d\n", par[0], par[1]);
    free(par);
}
#endif
#endif
