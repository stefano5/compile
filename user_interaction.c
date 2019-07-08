#ifndef USER_INTERACTION
#define USER_INTERACTION

void print_syntax(char **argv) {
    if (language == ITALIAN) {
        printf("Compila file C e C++                                                                                                                        "VERSION"\n"
                "\nSintassi: %s -[COMMAND] [PARAM]\n\n"
                "Dove\n"
                "      -[COMMAND] sono dei comandi, tutti opzionali, che possono influire sul comando che verra' generato ed eseguito. DEVONO iniziare con il trattino: '-'\n"
                "      [PARAM] sono dei parametri, sempre opzionali, e se inseriti verranno utilizzati solo i primi due. Tutti gli altri non verranno presi in considerazione\n"
                "L'uso del software dipende dai parametri che gli sono dati\n"
                "\nPARAMETRI:\n"
                "\t0 parametri: si sottointende che nella directory corrente sia presente un solo file compilabile, quindi verra' compilato e l'eseguibile avra' come nome quello del sorgente privato dell'estensione\n"
                "\t1 parametro: il parametro passato sara' il file che verra' compilato, l'eseguibile avra' come nome quello del sorgente privato dell'estensione\n"
                "\t2 parametri: il primo parametro sara' trattato esattamente come sopra, ma stavolta l'eseguibile avra' il nome del secondo parametro\n"
                "Il classico comando generato sara': \n"
                "gcc -Wall -Werror file.c -g -o file\n"
                "Tale comando e' modificabile utilizzando quindi dei comandi\n"
                "\nCOMANDI:\n"
                "\t-d o --debug             si vuole rimuovere il parametro '-Wall' in modo da rendere compilabile un file con lievi errori sintattici\n", argv[0]);
        printf("\t-l o \t--link-library   ");
        printf("si vogliono linkare delle eventuali librerie esterne. Tali librerie possono essere aggiunte con la seguente sintassi\n"
                "\t\t.  -al=library         in questo modo la libreria 'library' verra' aggiunta ogni qual volta si usera' il parametro '-l'\n"
                "\t\t.  Esempio, il comando: \n"
                "\t\t.\t %s -al=pthread\n"
                "\t\t.  Aggiungera' il link alla libreria pthread in fase di compilazione (e NESSUN file verra' compilato!), quindi da ora in poi quando si scrivera':\n"
                "\t\t.\t %s -l\n"
                "\t\t.  verra' generato un comando del tipo:\n"
                "\t\t.\t gcc -Wall -Werror file.c -g -lpthread -o file\n"
                "\t\t.  e sara' quindi possibile utilizzare la libreria pthread correttamente\n", argv[0], argv[0]);
        printf("\tSe si linka una libreria errata e' possibile usare il seguente comando: \n");
        BEGIN_PRINT_BLUE"\t--reset-library   "END_PRINT;
        printf("\t         ripristina file system delle librerie eliminando eventuali errori di inserimento\n"
                "\t-D=MACRO                 attiva la macro di nome 'MACRO'\n");
        BEGIN_PRINT_BLUE"\t--clear-register"END_PRINT;
        printf("\t         svuota cronologia delle compilazioni effettuate\n");
        BEGIN_PRINT_BLUE"\t--view-register"END_PRINT;
        printf("\t          apri editor di default e vedi la cronologia delle compilazioni effettuate\n");
        BEGIN_PRINT_BLUE"\t--change-editor"END_PRINT;
        printf("\t          cambia l'editor di default (passowrd di root richiesta)\n");
        BEGIN_PRINT_BLUE"\t--view-service   -v"END_PRINT;
        printf("\t         vedi lo stato dei servizi\n"

                "\t-ol o --open-loop        compila in anello aperto, il software non controllera' la buona riuscita della compilazione e si limitera' ad utilizzare i parametri scelti dall'utente\n"

                "\nMODALITA': \t\t(l'attivazione di un servizio e' permanente)\n"
                "\t\tNB: per ogni comando sotto riportato: NESSUN FILE VERRÀ COMPILATO!\n"
                "\t--set --show-command     dopo questo comando i comandi di compilazione generati verranno sempre mostrati a video\n"
                "\t--set --hide-Command     dopo questo comando i comandi di compilazione generati non verranno piu' mostrati a video\n"
                "\n"
                "\t--set --advanced-mode    effettua dei tentativi riducendo gradualmente la severità del compilatore fino al possibile. L'uso dei parametri '-d' e '-l' diventeranno inutili\n"
                "\t--set --normal-mode      rimuovi modalita' advanced\n"
                "\n"
                "\t--set --select-language  scegli quale lingua usare (EN/ITA)\n"
                "\n\n"
                "NOTE:      i ");
        BEGIN_PRINT_BLUE"comandi colorati in blu"END_PRINT; 
        printf(" non generano, e quindi non eseguono, nessun comando di compilazione. Nessun file verrà toccato\n"
                "\n"
                ); 
    } else {
        printf("C and C++ compiler                                                                                                                          "VERSION"\n"
                "\nSyntax: %s -[COMMAND] [PARAM]\n\n"
                "Where:\n"
                "      -[COMMAND] are a command, all optional, that can affect the command that will be generated and executed. Must start with the dash: '-'\n"
                "      [PARAM] are a parameter, also all optional, and if inserted, only the first two will be used. All others will not be taken into consideration\n"
                "The use of the software depends on the parameters given to it\n"
                "\nPARAMETERS:\n"
                "\t0 parameter:     it's implied that in the current directory there is only one compatible file, therefore it will be compiled and the executable will have by name that of the source without the extension.\n"
                "\t1 parameter:     the passed parameter will be the file that will be compiled, the executable will have the name of the source without the extension\n"
                "\t2 parameters     the first parameter will be treated exactly as above, but the executable will have the name of the second parameter\n"
                "A standard generated command will be:\n"
                "gcc -Wall -Werror file.c -g -o file\n"
                "This command can be modified using commands\n"
                "\nCOMMAND:\n"
                "\t-d o --debug             you want to remove the '-Wall' parameter so that we can compile a file with slight syntactic errors\n", argv[0]);
        printf("\t-l o \t--link-library   ");
        printf(
                "\t     you want to link any external libraries. These libraries can be added with the following syntax\n" 
                "\t\t.  -al=library         in this way the library will be added whenever the '-l' parameter is used\n"
                "\t\t.  Eg: \n"
                "\t\t.\t %s -al=pthread\n"
                "\t\t.  This command will add the link to the 'pthread' library at compile time (and no one file will be compiled!), so from now when writing:\n"
                "\t\t.\t %s -l\n"
                "\t\t.  a command like this will be generated:\n"
                "\t\t.\t gcc -Wall -Werror file.c -g -lpthread -o file\n"
                "\t\t.  and you can then use the 'pthread' library correctly\n"
                "\t-D=MACRO                 enable the macro named 'MACRO'\n", argv[0], argv[0]);
        BEGIN_PRINT_BLUE"\t--clear-register"END_PRINT;
                printf("\t          clear compilation history\n");
        BEGIN_PRINT_BLUE"\t--view-register"END_PRINT;
                printf("\t          displays the history of compilations made with the default editor\n");
        BEGIN_PRINT_BLUE"\t--change-editor"END_PRINT;
        printf(
                "\t          change the default editor (root privileges required)\n"
                "\t-ol o --open-loop        the software will not check the success of the compilation and therefore will use the parameters chosen by the user\n"
                "\nMODALITY: \t\t(service activation is permanent). \n"
                "\t\tNB: for each command shown below: NO ONE FILE WILL BE COMPILED!\n"
                "\t--set --show-command     after this command the generated compilation command will always be printed\n"
                "\t--set --hide-Command     after this command the generated compilation command will NOT be printed\n"
                "\n"
                "\t--set --advanced-mode    make attempts by gradually reducing the compiler's severity until possible. NB: The parameters '-d' and 'l' will becomes useless\n"
                "\t--set --normal-mode      remove advanced mode \n"
                "\n"
                "\t--set --select-language  choose which one langage to use (EN/ITA)\n"
                "\n\n"
                "NOTE:      the ");
        BEGIN_PRINT_BLUE"blue colored commands"END_PRINT; 
        printf(" do not generate, and therefore do not execute, any compilation command. No file will be processed\n"
                "\n"
               ); 
    }
}

void active_dtd() {
    if (language == ENGLISH) {
        printf("[BE CAREFUL] With the parameter '-dtd' the debug mode reserved for debugging this software will be activated, and not the one to be compiled\n");
        printf("If you want to compile a program ignoring the warnings use the '-d' command or use the -h command to get more info.\n");
        printf("Continue? (ctrl+c to cancel)\n");
    } else {
        printf("ATTENZIONE: con il parametro '-dtd' si attivera' la modalita' di debug riservata al debug di questo software, e non di quello che si vuole compilare\n");
        printf("Se vuoi compilare un programma ignorando i warning usa il comando '-d' oppure usa il comando -h per avere ulteriori info.\n");
        printf("Continuare? (ctrl+c per annullare)\n");
    }
    FFLUSH;
    debug_on();
}

void changePredefiniteEditor() {
    if (language == ENGLISH) {
        printf("[WARNING] This change will be permanent and all the software that will require an editor will do it based on this your next choice\n\n");
    } else {
        printf("[WARNING] Questa modifica sara' permanente e tutti i software che richiederanno un editor lo faranno sulla base di questa tua prossima scelta\n\n");
    }

    setColor(PRINT_MAGENTA);
    if (language == ENGLISH) {
        printf("\tIF YOU DO NOT WANT TO MAKE CHANGES, PRESS THE 'return' KEY TO THE NEXT REQUEST\n");
    } else {
        printf("\tSE NON VUOI EFFETTUARE MODIFICHE PREMI SEMPLICEMENTE IL TASTO 'Invio' ALLA PROSSIMA RICHIESTA\n");
    }
    resetColor();
    printf("\n");
    system("sudo update-alternatives --config editor");
}

void active_d() {
    setColor(PRINT_RED);
    if (language == ENGLISH) {
        printf("Debug mode activated. Wanrings will be ignored and the file, if possibile, will be compiled. Use this mode at your own risk\n");
    } else {
        printf("Modalita' di debug attiva. I warning verranno ignorati e il file, se possibile, compilato. Usa questa modalita' a tuo rischio e pericolo\n");
    }
    resetColor();
    compile_to_debug = 1;
}

int count_compatible_file(char **fileToCompile) {
    int countCompatibleFile=0;
    for (int i=0; i< Directory.n_file; i++) {
        char *type =(char*)memchr(Directory.name[i], '.', strlen(Directory.name[i]));
        if (type == NULL) continue;
        if (!strcmp(type, ".c") || !strcmp(type, ".c++") || !strcmp(type, ".cpp") || !strcmp(type, DISABLE_JAVA) || !strcmp(type, ".cc")) {
            if (containMainFunction(Directory.name[i])) {
                *fileToCompile = (char*)malloc(strlen(Directory.name[i]) + 1);
                initArray_str(*fileToCompile, strlen(Directory.name[i]) + 1);
                strcpy(*fileToCompile, Directory.name[i]);
                countCompatibleFile++;
            }
        }
    }
    return countCompatibleFile;
}

void show_source_file() {
    int countCorrectFormat=0;
    for (int i=0; i< Directory.n_file; i++) {
        char *type =(char*)memchr(Directory.name[i], '.', strlen(Directory.name[i]));
        if (type == NULL) continue;
        if (!strcmp(type, ".c") || !strcmp(type, ".c++") || !strcmp(type, ".cpp") || !strcmp(type, DISABLE_JAVA) || !strcmp(type, ".cc")) {
            countCorrectFormat++;
            printf("> %s", Directory.name[i]);
            if (containMainFunction(Directory.name[i])) {
                printf("    <= main detected");
            }
            printf("\n");
        }
    }

    if (language == ENGLISH) {
        printf("\nThere are %d compatible file, which one you want to build\n", countCorrectFormat);
    } else {
        printf("\nCi sono %d file compatibili, scegli quale vuoi compilare\n", countCorrectFormat);
    }
}

void abortProgramm(char *nameCommand) {
    printf("[");
    setColor(PRINT_RED);
    printf("Abort");
    resetColor();
    
    if (language == ENGLISH) {
        printf("] Command %s not found. Try %s -h to info\n", nameCommand, *p);
    } else {
        printf("] Comando %s sconosciuto. Prova %s -h per info\n", nameCommand, *p);
    }
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

int setLanguage() {
    char command[12];
    initArray_str(command, 12);
    if (language == ENGLISH) {
        printf("Chose your language (1 => english / 2 => italiano)\n");
    } else {
        printf("Scegli la lingua (1 => english / 2 => italiano)\n");
    }
    readString(command, 12);
    if (!strcmp(command, "1")) {
        setFileSystem(2, 't');
        return EXIT_SUCCESS;
    } else if (!strcmp(command, "2")) {
        setFileSystem(2, 'f'); 
        printf("Ok daje\n");
        return EXIT_SUCCESS;
    } else {
        if (language == ENGLISH) printf("[Error] insert only '1' or '2'\n");
        else printf("[Error] Inserisci solo o '1' o '2'\n");
        return EXIT_FAILURE;
    }
}

#endif
