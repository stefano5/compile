#ifndef __APISO
#define __APISO

#include    <stdio.h>
#include    <stdlib.h>
#include    <dirent.h>
#include    <pwd.h>
#include    <unistd.h>

#include    <management_date.c>
#include    <printColor.c>
#include    <debug.c>
#include    <coloredMessage.c>

#define     TRUE      1
#define     FALSE     0

void msleep(int ms) {
    usleep(ms * 1000);
}

/* 
 * Con 'force == TRUE' se eseguiamo il programma come root esso verra' trattato come semplice user
 * */
char user[32];
int getUserId(char *user, int disableRoot) {
    int uid = getuid();
    if (uid==0 && disableRoot == TRUE) {       //trattiamo l'user come semplice utente
        uid=1000;
        printf_d("[apiSO.c]->getUserId sei l'utente root ma sei stato disattivatto e sei stato trattato come user 1000\n");
    }

    if (getpwuid(uid)->pw_name == NULL) {
        printf("getpwuid failed, what is your user id? [userID@namePC:~$]\n>");
        readString(user, 32);
    } else {
        strcpy(user, getpwuid(uid)->pw_name);
    }
    return uid;
}

void getCurrentDirectory(char *dir) {
    initArray_str(dir, strlen((dir)));
    if (getcwd(dir, sizeof(dir)) == NULL) {
        perror("getCurrentDirectory() failed\n");
    }
}


/*
 * write text in the path 
 * @return -1 if fail, else the written bytes 
 */
int writeFile(char *path, char *text, char *mode) {
    FILE *f=fopen(path, mode);
    if (f == NULL) { printf("[%s->writeFile] %s not found\n", __FILE__, path); return -1; }
    int success=fprintf(f, "%s", text);
    fclose(f);
    if (success==-1) return -1;
    return success;
}

struct {
    char name[128][128];
    int n_file;
} Directory;

int read_directory(const char *path) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path)) != NULL) {
        int i=0;
        while ((ent = readdir(dir)) != NULL) {
            if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
                continue;
            strcpy(Directory.name[i++], ent->d_name);
        }
        closedir(dir);
        Directory.n_file = i;
        return 1;
    } else {
        printf("Directory %s not found\n", path);
        return 0;
    }
}

int removeFile(char *name) {
    FILE *f=fopen(name, "r");
    if (f==NULL) {
        if (debug()) printf("[%s->removeFile]File %s not found\n", __FILE__, name);
        return FALSE;
    }
    fclose(f);
    remove(name);
    return TRUE;
}

int existFile(char *file) {
    FILE *f = fopen(file, "r");
    if (f==NULL) return FALSE;
    fclose(f);
    return TRUE;
}


/*
 * Ritorna il livello della batteria, se la batteria è in carica il valore sarà positivo, se la batteria non è in carica il valore sarà negativo
 * Bug: Error 11 scaturisce quando ????
 */
int getLevelBattery(){
init_func:
    system("acpitool -b > /home/stefano/.battery.txt");
    char output[64]="";
    usleep(10000);
    FILE *f=fopen("/home/stefano/.battery.txt", "r");
    if (f == NULL) {
        writeFile("/home/stefano/log/crash_batteria.txt", "Error 11. File '.battery.txt' not found. Why?\n", "a+");
        setColor(PRINT_RED);
        printf("Error 11. File '.battery.txt' not found. Why?\n"); sleep(1); 
        resetColor();
        goto init_func;
    } //Permessi o acpitool non esistente
    fgets(output, 64, f);
    fclose(f);
    removeFile("/home/stefano/.battery.txt");
    trim(output);
    int offset;
    int level;
    int oldLevel=50;	//a caso
    for (int i=0; i<64; i++){
        if (output[i] == 58){
            char _level[7]="";
            if (debug()) printf("<%s>\n", output);
            if (output[i+2] == 68){ //Batteria NON in carica 
                offset=15;
                for (int j=0; j<5;j++)
                    _level[j]=output[i+j+offset];
                //printf("Level: <%s>\n", _level);
                level=atoi(_level) *-1;
                break;
            } else if (output[i+2] == 67){ //Batteria in Carica
                //printf("In carica\n");
                offset=12;
                for (int j=0; j<5;j++)
                    _level[j]=output[i+j+offset];
                level=atoi(_level);
                break;                                                                                                                                                          
            } else if (output[i+2] == 70){ //batteria carica al 100%                                                                                                                
                level=100;
                break;
            } else if (output[i+2] == 85){
                //errore interno del comando di lettura dello stato della batteria
                setColor(PRINT_RED);
                printf("Errore di acpitool, ha ritornato l'output: <%s> che non e' noto. E' stato tornato il vecchio valore letto\n", output);
                resetColor();
                return oldLevel;
            } else {        //Carattere sconosciuto. Potrebbe essere un errore scaturito dal comando acpitool. Un output non atteso?
                char report[128]="";
                sprintf(report, 
                        "[errore 33]Output: <%s> E' un output noto?\nTra questi caratteri ho guardato il carattere centrale: <%c%c%c> Data: %s\n",
                        output, output[i+1], output[i+2], output[i+3], getTime()
                       );
                writeFile("/home/stefano/log/crash_batteria.txt", report, "a+");
                printf("Errore 33\n");
                printf_d(report);
                return oldLevel;
            }
        }
    }
    if (level==0) { //se vero c'è un problema con l'offset del comando. L'output è cambiato?
        printf("Errore 44\n");
        char report[128]="";
        sprintf(report, "[errore 44]Data: %s. Output: <%s> E' un output noto?\n", getTime(), output);
        writeFile("/home/stefano/log/crash_batteria.txt", report, "a+");
        printf_d(report);
        exit(EXIT_FAILURE);
    }
    oldLevel = level;
    return level;
}

#endif
