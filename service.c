#ifndef SERVICE_C
#define SERVICE_C

// Path: /home/stefano/.compile.txt
// Il file contiene lo stato dei servizi del programma 
//
// Ogni carattere è indicatore di un servizio:
//     't' : true   servizio attivato
//     'f' : false  servizio disattivato
//
// Al momento abbiamo:
// fftt
// 1234
//
// 1: mostra a video il comando generato (t=si, f=no)
// 2: attiva modalità dummies (t=si, f=no)
// 3: usa programma in inglese (t=si, f=no=>quindi in italiano)
// 4: abilita intelligenza di compile


int managementModifySetting(char *command) {
    if (!strcasecmp(command, "--show-command")){
        setFileSystem(0, 't');
        return EXIT_SUCCESS;
    } else if (!strcasecmp(command, "--hide-command")) {
        setFileSystem(0, 'f');
        return EXIT_SUCCESS;
    //} else if (!strcasecmp(command, "--dummies-mode")){
    } else if (!strcasecmp(command, "--advanced-mode")){
        setFileSystem(1, 't');
        exit(EXIT_SUCCESS);
        return EXIT_SUCCESS;
    } else if (!strcasecmp(command, "--normal-mode")) {
        setFileSystem(1, 'f');
        return EXIT_SUCCESS;
    } else if (!strcmp(command, "--select-language")) {
        setLanguage();
        return EXIT_SUCCESS;
    } else if (!strcmp(command, "--ia-on") || !strcmp(command, "--enable-intelligence")) {
        setFileSystem(3, 't'); 
        return EXIT_SUCCESS;
    } else if (!strcmp(command, "--ia-off") || !strcmp(command, "--disable-intelligence")) {
        setFileSystem(3, 'f');
        return EXIT_SUCCESS;
    }
    printf("Errore di sintassi. Dopo '--set' deve seguire un altro comando noto. Usa il parametro -h per info \n");
    return EXIT_FAILURE;
}



int fileSystemCorrupt(char *setting, FILE *f) {
    char user[32];
    char path[64];
    getUserId(user, TRUE);
    sprintf(path, "/home/%s/.compile.txt", user);
    if (strlen(setting) != strlen(INITIALIZE_STATE_SERVICE)) {
        fclose(f);
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        f=fopen(path, "r");
        errorMessage("File system is corrupt. Bug detected :(\n");
        printf("setting: <%s>\n", setting);
        printf("INIT: <%s>\n", INITIALIZE_STATE_SERVICE);
        return TRUE;
    }
    return FALSE;
}

//Legge dal path ~/.compile_lib.txt le librerie da linkare
void readLibrary(char *lib, int dim) {
    char user[32];
    char path[64];
    initArray_str(lib, dim);
    initArray_str(user, 32);
    initArray_str(path, 64);

    getUserId(user, TRUE);
    sprintf(path, PATH_FILE_LIBRARY, user);
    FILE *f=fopen(path, "r");

    if (f == NULL) {
        writeFile(path, INIT_LIBRARY, "w");
        printf("[WARNING] Filesystem initialized. (3) Try again to initialize\n");
    } else {
        fgets(lib, dim, f);
        trim(lib);
        fclose(f);
    }
}

//aggiunge al file ~/compile_lib.txt una nuova libreria. SI FIDA CHE LA LIBRERIA PASSATA ESISTA
int addLibrary(char *param) {
    char lib[512];
    initArray_str(lib, 512);
    readLibrary(lib, 512);
    if (strstr(lib, param)) {
        if (language == ENGLISH)
            printf("The library '%s' already exist\n", param);
        else 
            printf("La libreria '%s' esiste gia'\n", param);
        return EXIT_FAILURE;
    }
    char user[32];
    char path[64];
    initArray_str(user, 32);
    initArray_str(path, 64);
    getUserId(user, TRUE);
    sprintf(path, PATH_FILE_LIBRARY, user);

    if (param[0] == '-' && param[1] == 'l') {    //Da versione 3 e superiore questa condizione non è più verificabile
        //ho scritto, ad esempio, -lpthread quindi sono stato bravo e metto tutto nel file
        sprintf(lib , "%s %s", lib, param);
    } else if (param[0] != 'l') {
        sprintf(lib, "%s -l%s", lib, param);
    } else {
        if (language == ENGLISH)
            printf("Parameter '%s' its undefined. Please give me '-h' parameter to get help\n", param);
        else
            printf("Il parametro '%s' è sconosciuto. Usa il parametro '-h' per info\n", param);
        return EXIT_FAILURE;
    }
    writeFile(path, lib, "w");
    return EXIT_SUCCESS;
}

//Visualizza 
void showCommand(char *cmd, char *fileToCompile, char *library, char *name_output) {
    //  Riga: [mostraComandoGenerato][?]
    //  value:t->true, f->false
    char user[32];
    char path[64];
    initArray_str(user, 32);
    initArray_str(path, 64);
    getUserId(user, TRUE);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem not initiliazed. (1) Try again to initialize \n");
    } else {
        char setting[12];
        initArray_str(setting, 12);
        fgets(setting, 12, f);
        trim(setting);
        if (fileSystemCorrupt(setting, f) == TRUE) 
            fgets(setting, 12, f);

        if (setting[0] == 't' || forceCompilation == 1)
            printCommand(cmd, fileToCompile, library, macro, name_output);
        fclose(f);
    }
}

//Sovrascrive il file system con il nuovo parametro
void setFileSystem(int param, char newSet) {
    char user[32];
    char path[64];
    initArray_str(user, 32);
    initArray_str(path, 64);
    getUserId(user, TRUE);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem not initiliazed. (2) Try again to initialize \n");
        return;
    }
    char setting[12];
    initArray_str(setting, 12);
    fgets(setting, 12, f);
    trim(setting);
    if (fileSystemCorrupt(setting, f) == TRUE)
        fgets(setting, 12, f);
    fclose(f);

    f = fopen(path, "w");
    char newSetting[12];
    initArray_str(newSetting, 12);

    for (int i=0; i<strlen(setting); i++) {
        if (i == param)
            newSetting[i] = newSet;
        else 
            newSetting[i] = setting[i];
    }
    writeFile(path, newSetting, "w");
    fclose(f);
}

int dummiesMode() {
    char user[32];
    char path[64];
    initArray_str(user, 32);
    initArray_str(path, 64);
    getUserId(user, TRUE);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem not initiliazed. (2) Try again to initialize \n");
    } else {
        char setting[12];
        initArray_str(setting, 12);
        fgets(setting, 12, f);
        trim(setting);
        if (fileSystemCorrupt(setting, f) == TRUE) 
            fgets(setting, 12, f);
        fclose(f);
        //printf("service 0: %c\nservice 1: %c\n", setting[0], setting[1]);
        if (setting[1] == 't') 
            return TRUE;
        return FALSE;
    }
    return FALSE;
}

int getLanguage() {
    char user[32];
    char path[64];
    initArray_str(user, 32);
    initArray_str(path, 64);
    getUserId(user, TRUE);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem not initiliazed. (4) Try again to initialize \n");
    } else {
        char setting[12];
        initArray_str(setting, 12);
        fgets(setting, 12, f);
        trim(setting);
        if (fileSystemCorrupt(setting, f) == TRUE)
            fgets(setting, 12, f);
        fclose(f);

        //printf("service 0: %c\nservice 1: %c\n", setting[0], setting[1]);
        if (setting[2] == 't') 
            return ENGLISH;
        return ITALIAN;
    }
    return ENGLISH;
}


/*
 * Se force == TRUE non verrà guardata la modalità di debug
 * altrimenti lo stato verrà mostrato solo se la modalità di debug è stata attivata
 * */
void viewServiceState(int force) {
    if (debug() || force == TRUE) {
        char user[32];
        char path[64];
        initArray_str(user, 32);
        initArray_str(path, 64);
        getUserId(user, TRUE);
        sprintf(path, "/home/%s/.compile.txt", user);
        FILE *f = fopen(path, "r");
        if (f == NULL) {
            writeFile(path, INITIALIZE_STATE_SERVICE, "w");
            printf("[WARNING] Filesystem not initiliazed. (5) Try again to initialize \n");
        } else {
            char service[12];
            initArray_str(service, 12);
            fscanf(f, "%c%c%c%c", &service[0], &service[1], &service[2], &service[3]);
            if (fileSystemCorrupt(service, f) == TRUE) 
                fscanf(f, "%c%c%c%c", &service[0], &service[1], &service[2], &service[3]);                                                       //QUI MODIFICHE AL FILE SYSTEM PER I SERVIZI
            fclose(f);
            printf("\t\tThis is '%s'                    Version: %s\n", p[0], VERSION);
            printf("\t\t+-------------------------------------------------------------+\n");
            printf("\t\t|        View status of services                              |\n");
            printf("\t\t|                                                             |\n");

            for (int i=0; i<4; i++) {
                if (i==0)
                    printf("\t\t| View generated command:  ");
                if (i == 1) 
                    printf("\t\t| Advanced mode:           ");
                else if (i == 2) 
                    printf("\t\t| Use english package:     ");
                else if (i == 3) 
                    printf("\t\t| Artificial intelligence: ");


                if (service[i] == 't') {
                    setColor(PRINT_GREEN);
                    printf("enabled ");
                    resetColor();
                } else {
                    setColor(PRINT_RED);
                    printf("disabled");
                    resetColor();
                }
                printf("                           |\n");
            }
            printf("\t\t|                                                             |\n");
            printf("\t\t+-------------------------------------------------------------+\n");
        }
    }
}

void resetLibrary() {
    char user[32];
    char path[64];
    initArray_str(user, 32);
    initArray_str(path, 64);
    getUserId(user, TRUE);
    sprintf(path, "/home/%s/.compile_lib.txt", user);
    writeFile(path, INIT_LIBRARY, "w");
    if (language == ENGLISH)
        printf("Reset saved ibrary. Now are: '%s'", INIT_LIBRARY);
    else
        printf("Ripristino librerie salvate. Adesso sono: %s\n", INIT_LIBRARY);
}

/*
 * Questa funzione è eseguita solo dal processo figlio
*/
int runAutomatic(char *nameExe) {
    char commandExe[128];
    initArray_str(commandExe, 128);
    sprintf(commandExe, "echo \"\" && ./%s && touch .success_child", nameExe);
    system(commandExe);
    if (existFile(".success_child") == TRUE) successMessage("Child success");
    else errorMessage("Child failed");
    removeFile(".success_child");
    return (existFile(".success_child") == TRUE ? EXIT_SUCCESS : EXIT_FAILURE);

}

int iaIsEnable() {//se l'intelligenza è attivata torna true altrimenti false    
    char user[32];
    char path[64];
    initArray_str(user, 32);
    initArray_str(path, 64);
    getUserId(user, TRUE);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem not initiliazed. (6) Try again to initialize \n");
    } else {
        char setting[12];
        initArray_str(setting, 12);
        fgets(setting, 12, f);
        trim(setting);
        if (fileSystemCorrupt(setting, f) == TRUE)
            fgets(setting, 12, f);
        fclose(f);

        return setting[3] == 't';
    }
    return FALSE;
}


#endif
