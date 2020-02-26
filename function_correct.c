#ifndef FUNCTION_CORRECT
#define FUNCTION_CORRECT

#define PATH_FILE_LIBRARY           "/home/%s/.compile_lib.txt"
#define INITIALIZE_STATE_SERVICE     "ff"

extern char    macro[256];
extern int     howColor;
extern int     forceCompilation;
extern int     enableCompilationAttempts;
extern int     compile_to_debug;
extern char    **p;

//Legge dal path ~/.compile_lib.txt le librerie da linkare
void readLibrary(char *lib, int dim) {
    char user[32];
    char path[64];
    for (int i=0; i<dim; i++) lib[i] = '\0';
    for (int i=0; i<32; i++) user[i] = '\0';
    for (int i=0; i<64; i++) path[i] = '\0';
    getUserId(user);
    sprintf(path, PATH_FILE_LIBRARY, user);
    FILE *f=fopen(path, "r");

    if (f == NULL) {
        writeFile(path, "-lpthread -lm -lrt", "w");
        printf("[WARNING] Filesystem initilized. (3) Try again\n");
    } else {
        fgets(lib, dim, f);
        trim(lib);
        fclose(f);
    }
}

//aggiunge al file ~/compile_lib.txt una nuova libreria. SI FIDA CHE LA LIBRERIA PASSATA ESISTA
void addLibrary(char *param) {
    char lib[512];
    initArray_str(lib, 512);
    readLibrary(lib, 512);

    char user[32];
    char path[64];
    for (int i=0; i<32; i++) user[i] = '\0';
    for (int i=0; i<64; i++) path[i] = '\0';
    getUserId(user);
    sprintf(path, PATH_FILE_LIBRARY, user);

    if (param[0] == '-' && param[1] == 'l') {
        //ho scritto, ad esempio, -lpthread quindi sono stato bravo e metto tutto nel file
        sprintf(lib , "%s %s", lib, param);
    } else if (param[0] != '0' && param[1] != 'l') {    //Da versione 3 e superiore questa condizione non è più verificabile
        sprintf(lib, "%s -l%s", lib, param);
    } else {
        printf("Parametro '%s' non noto. Premi -h per aiuto\n", param);
        return;
    }
    writeFile(path, lib, "w");
}

//Aggiunge una o piu' macro passate come parametro/i in compilazione
void addMacro(char *mcr) {
    sprintf(macro, "%s -D%s ", macro, mcr);
}

//Stampa il comando generato colorandolo
void printCommand(char *cmd, char *fileToCompile, char *library, char *_macro, char *name_output) {
    switch (howColor) {
        case 1:
            setColor(PRINT_MAGENTA);
            printf("gcc ");
            setColor(PRINT_UNDERLINE);
            printf("%s ", fileToCompile);
            setColor(PRINT_BLUE);
            printf("-g ");
            setColor(PRINT_YELLOW);
            printf("%s ", library);
            setColor(PRINT_RED);
            printf("%s ", _macro);
            setColor(PRINT_WHITE);
            printf("-o ");
            setColor(PRINT_GREEN);
            printf("%s\n", name_output);
            break;
        case 2:
            //           sprintf(cmd, "gcc -Wall -Werror %s -g %s -o %s", fileToCompile, library, name_output);
            setColor(PRINT_MAGENTA);
            printf("gcc ");
            setColor(PRINT_RED);
            printf("-Wall -Werror ");
            setColor(PRINT_UNDERLINE);
            printf("%s ", fileToCompile);
            setColor(PRINT_BLUE);
            printf("-g ");
            setColor(PRINT_YELLOW);
            printf("%s ", library);
            setColor(PRINT_RED);
            printf("%s ", _macro);
            setColor(PRINT_WHITE);
            printf("-o ");
            setColor(PRINT_GREEN);
            printf("%s\n", name_output);
            break;
        case 3:
            //           sprintf(cmd, "g++ %s -g %s -o %s", fileToCompile, library, name_output);
            setColor(PRINT_MAGENTA);
            printf("g++ ");
            setColor(PRINT_UNDERLINE);
            printf("%s ", fileToCompile);
            setColor(PRINT_BLUE);
            printf("-g ");
            setColor(PRINT_YELLOW);
            printf("%s ", library);
            setColor(PRINT_RED);
            printf("%s ", _macro);
            setColor(PRINT_WHITE);
            printf("-o ");
            setColor(PRINT_GREEN);
            printf("%s\n", name_output);
            break;
        case 4:
            //           sprintf(cmd, "g++ -Wall -Werror %s -g %s -o %s", fileToCompile, library, name_output);
            setColor(PRINT_MAGENTA);
            printf("g++ ");
            setColor(PRINT_RED);
            printf("-Wall -Werror ");
            setColor(PRINT_UNDERLINE);
            printf("%s ", fileToCompile);
            setColor(PRINT_BLUE);
            printf("-g ");
            setColor(PRINT_YELLOW);
            printf("%s ", library);
            setColor(PRINT_RED);
            printf("%s ", _macro);
            setColor(PRINT_WHITE);
            printf("-o ");
            setColor(PRINT_GREEN);
            printf("%s\n", name_output);
            break;
        case 5:
            setColor(PRINT_MAGENTA);
            printf("java ");
            setColor(PRINT_GREEN);
            printf("%s \n", fileToCompile);
            break;
        default: 
            printf("comando generato: %s\n", cmd);
    }
    resetColor();
}

//Visualizza 
void showCommand(char *cmd, char *fileToCompile, char *library, char *name_output) {
    //  Riga: [mostraComandoGenerato][?]
    //  value:t->true, f->false
    char user[32];
    char path[64];
    for (int i=0; i<32; i++) user[i] = '\0';
    for (int i=0; i<64; i++) path[i] = '\0';
    getUserId(user);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem non inizializzato. (1) Da adesso saranno disponibili i servizi\n");
    } else {
        char setting[12];
        fgets(setting, 12, f);
        trim(setting);
        if (setting[0] == 't' || forceCompilation == 1)
            printCommand(cmd, fileToCompile, library, macro, name_output);
        fclose(f);
    }
}

//Sovrascrive il file system con i nuovi parametri
void setFileSystem(int param, char newSet) {
    char user[32];
    char path[64];
    for (int i=0; i<32; i++) user[i] = '\0';
    for (int i=0; i<64; i++) path[i] = '\0';
    getUserId(user);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem non inizializzato. (2) Da adesso saranno disponibili i servizi\n");
        return;
    }
    char setting[12];
    fgets(setting, 12, f);
    trim(setting);
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
    for (int i=0; i<32; i++) user[i] = '\0';
    for (int i=0; i<64; i++) path[i] = '\0';
    getUserId(user);
    sprintf(path, "/home/%s/.compile.txt", user);
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        writeFile(path, INITIALIZE_STATE_SERVICE, "w");
        printf("[WARNING] Filesystem non inizializzato. (3) Da adesso saranno disponibili i servizi\n");
    } else {
        char setting[12];
        fgets(setting, 12, f);
        fclose(f);
        trim(setting);
        //printf("service 0: %c\nservice 1: %c\n", setting[0], setting[1]);
        if (setting[1] == 't') 
            return TRUE;
        return FALSE;
    }
    return FALSE;
}

void managementModifySetting(char *command) {
    if (!strcasecmp(command, "--show-command")){
        setFileSystem(0, 't');
        exit(EXIT_SUCCESS);
    } else if (!strcasecmp(command, "--hide-command")) {
        setFileSystem(0, 'f');
        exit(EXIT_SUCCESS);
    }

    if (!strcasecmp(command, "--dummies-mode")){
        setFileSystem(1, 't');
        exit(EXIT_SUCCESS);
    } else if (!strcasecmp(command, "--normal-mode")) {
        setFileSystem(1, 'f');
        exit(EXIT_SUCCESS);
    }
}

void assign_name(char *name_file, char *name_output){
    for (int i=0; name_file[i]!='.'; i++) {
        name_output[i]=name_file[i];
    }
}

/*
 * Esaminiamo la directory "." e vediamo se esiste un unico file compatibile alla compilazione
 */
char *uniqueFile;       //qui scriviamo l'eventuale file compatibile alla compilazione trovato in una directory
int search_single_file() {
    read_directory(".");
    int numberFile=0;
    for (int i=0; i< Directory.n_file; i++) {
        char *type =(char*)memchr(Directory.name[i], '.', strlen(Directory.name[i]));
        if (type == NULL) continue; //perchè il file guardato non ha nessuna estensione 
        if(debug()) printf("Vedo il file %s\n", Directory.name[i]);
        if (!strcmp(type, ".c") || !strcmp(type, ".c++") || !strcmp(type, ".cpp") || !strcmp(type, ".java") || !strcmp(type, ".cc")) {
            printf_d("\tE riconosco che ha una estensione nota\n");
            if (numberFile==0) {
                printf_d("\t\tEd e' il primo che trovo [mi aspetto una sola stampa]\n");
                uniqueFile = (char*)malloc(strlen(Directory.name[i]) + 1);
                strcpy(uniqueFile, Directory.name[i]);
                numberFile++;
            } else if (numberFile > 0) {
                free(uniqueFile);
                return -1;
            }
        }
    }
    return numberFile;
}

void print_syntax(char **argv) {
    printf("Compila file C, C++ e genera bytecode per file .java                                                                                                     V. 4.0 AP OP\n"   //Analyze Param OPtimization
            "\nSintassi: %s -[COMMAND] [PARAM]\n\n"
            "Dove\n"
            "      -[COMMAND] sono dei comandi, tutti opzionali, che possono influire sul comando che verra' generato ed eseguito. DEVONO iniziare con il trattino: '-'\n"
            "      PARAM sono dei parametri, sempre opzionali, e se inseriti verranno utilizzati solo i primi due. Tutti gli altri non verranno presi in considerazione\n"
            "L'uso del software dipende dai parametri che gli sono dati\n"
            "\nPARAMETRI:\n"
            "\t0 parametri: si sottointende che nella directory corrente sia presente un solo file compilabile, quindi verra' compilato e l'eseguibile avra' come nome quello del sorgente privato dell'estensione\n"
            "\t1 parametro: il parametro passato sara' il file che verra' compilato, l'eseguibile avra' come nome quello del sorgente privato dell'estensione\n"
            "\t2 parametri: il primo parametro sara' trattato esattamente come sopra, ma stavolta l'eseguibile avra' il nome del secondo parametro\n"
            "Il classico comando generato sara': \n"
            "gcc -Wall -Werror file.c -g -o file\n"
            "Tale comando e' modificabile utilizzando quindi dei comandi\n"
            "\nCOMANDI:\n"
            "\t-d o --debug     si vuole rimuovere il parametro '-Wall' in modo da rendere compilabile un file con lievi errori sintattici\n"
            "\t-l o --link-library      si vogliono linkare delle eventuali librerie esterne. Tali librerie possono essere aggiunte con la seguente sintassi\n"
            "\t\t.  -al=library         in questo modo la libreria 'library' verra' aggiunta ogni qual volta si usera' il parametro '-l'\n"
            "\t\t.  Esempio, il comando: \n"
            "\t\t.\t %s -al=pthread\n"
            "\t\t.  Aggiungera' il link alla libreria pthread in fase di compilazione (e NESSUN file verra' compilato!), quindi da ora in poi quando si scrivera':\n"
            "\t\t.\t %s -l\n"
            "\t\t.  verra' generato un comando del tipo:\n"
            "\t\t.\t gcc -Wall -Werror file.c -g -lpthread -o file\n"
            "\t\t.  e sara' quindi possibile utilizzare la libreria pthread correttamente\n"
            "\t-D=MACRO                  attiva la macro di nome 'MACRO'\n"
            "\t--clear-register          svuota cronologia delle compilazioni effettuate\n"
            "\t--view-register           apri editor di default e vedi la cronologia delle compilazioni effettuate\n"
            "\t--change-editor           cambia l'editor di default (passowrd di root richiesta)\n"
            "\t-ol o --open-loop         compila in anello aperto, il software non controllera' la buona riuscita della compilazione e si limitera' ad utilizzare i parametri scelti dall'utente\n"
            "\nMODALITA': \t\t(l'attivazione di un servizio e' permanente)\n"
            "\t--set --show-command      dopo questo comando i comandi di compilazione generati verranno sempre mostrati a video\n"
            "\t--set --hide-Command      dopo questo comando i comandi di compilazione generati non verranno piu' mostrati a video\n"
            "\n"
            "\t--set --dummies-mode      ammorbidisci la compilazione riducendo gradualmente la severità dei compilatori\n"
            "\t--set --normal-mode       rimuovi modalita' 'for dummies'\n"
            "\n\n"
            "NOTE:\n"
            "\tDalla versione 4 AP verranno fatti tre tentativi di compilazione di default, nell'ordine:\n"
            "\t\t1) Comando diretto dall'utente\n"
            "\t\t2) Tentativo di compilazione con parametro '-l'\n"
            "\t\t3) Tentativo di compilazione con parametro '-d' e '-l'\n"
            , argv[0], argv[0], argv[0]
            );
}

void disableCompilationAttempts() {
    enableCompilationAttempts = FALSE;
}

void active_dtd() {
    printf("ATTENZIONE: con il parametro '-dtd' si attivera' la modalita' di debug riservata al debug di questo software, e non di quello che si vuole compilare\n");
    printf("Se vuoi compilare un programma ignorando i warning usa il comando '-d' oppure usa il comando -h per avere ulteriori info.\n");
    printf("Continuare? (ctrl+c per annullare)\n");
    getchar();
    debug_on();
}

void active_d() {
    setColor(PRINT_RED);
    printf("Modalita' di debug attiva. I warning verranno ignorati e il file, se possibile, compilato. Usa questa modalita' a tuo rischio e pericolo\n");
    resetColor();
    compile_to_debug = 1;
}

void show_error_much_file() {
    int countCorrectFormat=0;
    for (int i=0; i< Directory.n_file; i++) {
        char *type =(char*)memchr(Directory.name[i], '.', strlen(Directory.name[i]));
        if (type == NULL) continue;
        if (!strcmp(type, ".c") || !strcmp(type, ".c++") || !strcmp(type, ".cpp") || !strcmp(type, ".java") || !strcmp(type, ".cc")) {
            countCorrectFormat++;
            printf(">%s\n", Directory.name[i]);
        }
    }
    printf("\nSono %d file compatibili, specifica quale vuoi compilare\n", countCorrectFormat);
}

void writeIntoFileCommand(char *cmd) {
    char user[32];
    char path[64];
    char cwd[128];
    char text[256];
    initArray_str(user, 32);
    initArray_str(path, 64);
    initArray_str(cwd, 128);
    initArray_str(text, 256);

    getUserId(user);
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        sprintf(cwd, "%s",strerror(errno)); //get path
    }

    sprintf(path, "/home/%s/.compile_lastCommand.txt", user);

    sprintf(text, "%s \t\tgenerated on: %s\t\ton%s\n", cmd, getTime(), cwd);

    writeFile(path, text, "a+");
}

void removeRegister() {     //registro delle compilazioni
    char user[32];
    char path[128];
    initArray_str(user, 32);
    initArray_str(path, 128);

    getUserId(user);

    sprintf(path, "/home/%s/.compile_lastCommand.txt", user);
    removeFile(path);
}

//sudo update-alternatives --config editor
void viewRegister() {
    char user[32];
    char path[128];
    char cmd[256];
    initArray_str(user, 32);
    initArray_str(path, 128);
    initArray_str(cmd, 256);

    getUserId(user);

    sprintf(path, "/home/%s/.compile_lastCommand.txt", user);
    sprintf(cmd, "editor %s", path);
    system(cmd);                                        //apri l'editor predefinito e permettimi di modificare il file
}

void changePredefiniteEditor() {
    printf("[NOTA BENE] Questa modifica sara' permanente e tutti i software che richiederanno un editor lo faranno sulla base di questa tua prossima scelta\n\n");
    setColor(PRINT_MAGENTA);
    printf("\tSE NON VUOI EFFETTUARE MODIFICHE PREMI SEMPLICEMENTE IL TASTO 'Invio' ALLA PROSSIMA RICHIESTA\n");
    resetColor();
    printf("\n");
    system("sudo update-alternatives --config editor");
}

void managementParam(int index) {
    //nothing to do 
}

void abortProgramm(char *nameCommand) {
    printf("[");
    setColor(PRINT_RED);
    printf("Abort");
    resetColor();
    printf("] Comando %s sconosciuto. Prova %s -h per info\n", nameCommand, *p);
}

#endif
