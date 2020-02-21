/*
 * qui funzioni di intelligenza per il software compile
 *
 * 1° guarda l'ultima compilazione fatta, se è stata fatta allo stesso file negli ultimi 10 minuti allora manda in esecuzione il file ad avvenuta compilazione
 *
*/

#ifndef IA_C
#define IA_C

#include <function.h>

void clearsCounter(char *nameFile);

#define PATH_LAST_COMPILATED_FILE               "/home/%s/.lastCompilatedFile"              /*path file system*/
#define MAXIMUM_TIME_FROM_LAST_COMPILATION      10                                          /*tempo massimo dall'ultima compilazione entro cui il software viene mandato in esecuzione*/
#define PATH_COUNT_COMPILATION                  ".timeCompilation"                          /*qui salviamo il numero di compilazioni su di un file*/

int getCountCompilation(char *nameFile) {
    char row[32];
    FILE *f = fopen(nameFile, "r");
    if (f == NULL) {
        writeFile(nameFile, "0", "w");
        return 0;
    }

    initArray_str(row, 32);
    fgets(row, 32, f);
    fclose(f);

    return atoi(row);
}

void increaseCountCompilation(char *nameFile) {
    char count[12];
    initArray_str(count, 12);
    int count_i = getCountCompilation(nameFile);
    sprintf(count, "%d\n", count_i + 1);
    if (existFile(nameFile))
        writeFile(nameFile, count, "w");
    else 
        errorMessage("Unable to increase counter (IA)\n");
}

void clearsCounter(char *nameFile) {
    removeFile(nameFile);
}

/*
 * esegui automaticamente il file appena compilato se:
 *   1° lo stesso file è stato già compilato almeno 5 volte
 *   2° l'ultima compilazione di cui sopra è avvenuta entro massimo 15 minuti
 */
int  autoExeSw(char *nameFile) {
    char *timestamp = getHours();
    char lastCompilatedFile[64];
    char file[2][128];
    initArray_str(lastCompilatedFile, 64);
    initArray_str(file[0], 128);
    initArray_str(file[1], 128);

    getUserId(user, TRUE);
    sprintf(lastCompilatedFile, PATH_LAST_COMPILATED_FILE, user);
    FILE *f = fopen(lastCompilatedFile, "r");
    if (f == NULL) {
        sprintf(file[0], "%s\n", nameFile);
        sprintf(file[1], "%s\n", timestamp);
        writeFile(lastCompilatedFile, file[0], "w");
        writeFile(lastCompilatedFile, file[1], "a");
        return FALSE;
    } else {
        fgets(file[0], 128, f);     //namefile
        fgets(file[1], 128, f);     //timestamp
        fclose(f); 
        trim(file[0]);
        trim(file[1]);

        strcat(nameFile, "\n");
        strcat(timestamp, "\n");

        writeFile(lastCompilatedFile, nameFile, "w");
        writeFile(lastCompilatedFile, timestamp, "a");

        if (!strcmp(trim(nameFile), file[0])) {
            increaseCountCompilation(PATH_COUNT_COMPILATION);

            if (getCountCompilation(PATH_COUNT_COMPILATION) > 4) {
                int *par = calculatesDifference(file[1], getHours());
                if (par[1] < MAXIMUM_TIME_FROM_LAST_COMPILATION) {
                    free(par);
                    return TRUE;
                }
                free(par);
            }
        } else clearsCounter(PATH_COUNT_COMPILATION);
        return FALSE;
    }
}


#endif
