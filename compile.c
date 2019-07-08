#include <function.h>
#include <coloredMessage.c>
#include <errno.h>

#include "compile.h"
#include "build_command.c"
#include "service.c"
#include "user_interaction.c"

//             output input     input          input        input    input      input
//                ^     ^         ^              ^            ^        ^         ^
//create_command(cmd, argv, offset_param, compile_to_debug, type, name_output, macro);
void create_command(char *cmd, char *fileToCompile, int compile_to_debug, char *type, char *name_output, char *library, char *macro) {
    initArray_str(cmd, 1024);

    if (debug()) printf("File: %s. Output: %s\n", fileToCompile, name_output);
    if (!strcmp(type, ".c")) {
        if (compile_to_debug) {
            sprintf(cmd, "gcc %s -g %s %s -o %s", fileToCompile, library, macro, name_output);
            howColor = 1;
        } else {
            sprintf(cmd, "gcc -Wall -Werror %s -g %s %s -o %s", fileToCompile, library, macro, name_output);
            howColor = 2;
        }
    } else if (!strcmp(type, ".c++") || !strcmp(type, ".cpp") || !strcmp(type, ".cc")) {
        if (compile_to_debug) {
            howColor = 3;
            sprintf(cmd, "g++ %s -g %s %s -o %s", fileToCompile, library, macro, name_output);
        } else {
            howColor = 4;
            sprintf(cmd, "g++ -Wall -Werror %s -g %s %s -o %s", fileToCompile, library, macro, name_output);
        }
    } else if (!strcmp(type, DISABLE_JAVA)) {
        if (compile_to_debug) {
            printf("Nessun warning da ignorare con compilazione per file .java\n");
        }
        howColor = 5;
        sprintf(cmd, "javac %s", fileToCompile);
    } else {
        printf("Formato [%s] non supportato, rip\n", type);
        exit(EXIT_FAILURE);
    }

    showCommand(cmd, fileToCompile, library, name_output);
    if(debug()) printf("Comando generato: %s\n", cmd);
    writeIntoFileCommand(cmd);
}

void managementCommand(int index) {
    if (!strcmp(command[index], "-dtd") || !strcmp(command[index], "--debug-to-developer")) {
        active_dtd();
    } else if (!strcmp(command[index], "-d") || !strcmp(command[index], "--debug")) {
        active_d();
    } else if (!strcmp(command[index], "-h") || !strcmp(command[index], "--help")) {
        print_syntax(p);
        exit(EXIT_SUCCESS);
    } else if (!strcmp(command[index], "--set")) {
        exit(managementModifySetting(command[index + 1]));
    } else if (!strcmp(command[index], "-f") || !strcmp(command[index], "--force")) {
        forceCompilation = 1;
    } else if (!strcmp(command[index], "-l") || !strcmp(command[index], "--link-library")) {
        linkLibrary = 1;
    } else if (command[index][0] == '-' && command[index][1] == 'a' &&  command[index][2] == 'l' && command[index][3] == '=') {     //Linka librerie esterne
        subString(command[index], 4, strlen(command[index]));
        if (addLibrary(command[index]) == TRUE);
        printf("Libreria aggiunta\n");
        exit(EXIT_SUCCESS);
    } else if (command[index][0] == '-' && command[index][1] == 'D' && command[index][2] == '=') {      //Attiva macro
        subString(command[index], 3, strlen(command[index]));
        addMacro(command[index]);
    } else if (!strcmp(command[index], "--clear-register")) {
        removeRegister();
        printf("Registro compilazioni svuotato\n");
        exit(EXIT_SUCCESS);
    } else if (!strcmp(command[index], "--view-register")) {
        printf("Verrà usato il tuo editor predefinito. Se vuoi cambiarlo passami il parametro '--change-editor'\n");
        viewRegister();
        exit(EXIT_SUCCESS);
    } else if (!strcmp(command[index], "--change-editor")) {
        changePredefiniteEditor();
        exit(EXIT_SUCCESS);
    } else if (!strcmp(command[index], "-ol") || !strcmp(command[index], "--open-loop")) {
        disableCompilationAttempts();
    } else if (!strcmp(command[index], "-sl") || !strcmp(command[index], "--select-language")) {
        setLanguage();
        exit(EXIT_SUCCESS);
    } else if (!strcmp(command[index], "-v") || !strcmp(command[index], "--view-service")) {
        viewServiceState(TRUE);
        exit(EXIT_SUCCESS);
    } else if (!strcmp(command[index], "-r") || !strcmp(command[index], "--reset-library")) {
        resetLibrary(); 
        exit(EXIT_SUCCESS);
    } else {
        abortProgramm(command[index]);
        if (debug())
            printf("Primi 4 caratteri: %c%c%c%c\n", command[index][0], command[index][1], command[index][2], command[index][3]);
        exit(EXIT_FAILURE);
    }
}

int compilationSuccessful() {
    if (existFile(".successful")) {
        resultCompilation = TRUE;
        removeFile(".successful");
        return TRUE;
    } else {
        resultCompilation = FALSE;
        return FALSE;
    }
}


void runCommand(char *cmd, char *fileToCompile, int compile_to_debug, char *type, char *name_output, char *library, char *macro) {
    char command[1024];
    initArray_str(command, 1024);
    sprintf(command, "%s && echo 1 > .successful", cmd);
    
    if (!enableCompilationAttempts || dummiesMode() == FALSE) {
        system(command);
        compilationSuccessful();
        return;
    }

    for (int i=0; i<4; i++) {
        system(command);
        if (compilationSuccessful()) {
            break;
        }

        if (i == 0) {
            system("clear");
            printf("[");
            setColor(PRINT_CYAN);
            printf("FAILED 1/3");
            resetColor();
            printf("] Primo tentativo di compilazione fallito, verra' attivata la modalita' di debug\n");
            create_command(command, fileToCompile, 1, type, name_output, library, macro);
        } else if (i == 1) {
            system("clear");
            printf("[");
            setColor(PRINT_CYAN);
            printf("FAILED 2/3");
            resetColor();
            printf("] Secondo tentativo di compilazione fallito, verranno adesso linkate le librerie. -Wall settato\n");
            readLibrary(library, 512);
            create_command(command, fileToCompile, 0, type, name_output, library, macro);
        } else if (i == 2) {    //sblocchiamo tutto
            system("clear");
            printf("[");
            setColor(PRINT_CYAN);
            printf("FAILED 3/3");
            resetColor();
            printf("] Terzo tentativo di compilazione fallito, verranno adesso linkate le librerie e sara' abilitata la modalita' di debug\n");
            //readLibrary(library, 512);
            create_command(command, fileToCompile, 1, type, name_output, library, macro);
        }

        sprintf(command, "%s && echo 1 > .successful", command);
    }
}


void managementArg() {
    /*
    //Fa il main per semplicità di scope
    if (countParam != 0) {
    for (int i=0; i<countParam; i++) {
    managementParam(i);
    }
    }
    */

    if (countCommand != 0) {
        for (int i=0; i<countCommand; i++) {
            managementCommand(i);
        }
    }
}

// L'idea è:
// Leggiamo la directory, passiamo a gcc tutti i file .c e facciamo fare tutto a lui fidandici speranzosamente
//
// comando:
//
// gcc -Wall -Werror main.c other.c othe1.c ... othern.c -o -g main.c 
//
void tryToForce(char **fileToCompile, char **newTipe) {
    char mainFile[12];
    char othersFile[256];
    char *dumpType;
    char type[6];
    initArray_str(mainFile, 12);
    initArray_str(othersFile, 256);
    initArray_str(mainFile, 12);

    read_directory(".");

    for (int i=0; i< Directory.n_file; i++) {
        dumpType = (char*)memchr(Directory.name[i], '.', strlen(Directory.name[i]));            //substring al '.'
        if (dumpType == NULL || !strcmp(dumpType, DISABLE_JAVA)) continue;
        if (!strcmp(dumpType, ".c") || !strcmp(dumpType, ".c++") || !strcmp(dumpType, ".cpp") || !strcmp(dumpType, ".cc")) {
            if (strstr(Directory.name[i], "main") != NULL) {
                printf("Main rilevato\n");
                strcpy(mainFile, Directory.name[i]);
                strcpy(type, dumpType);
                break;
            }
        }
    }

    if (strlen(mainFile) > 0) {
        free(*fileToCompile);
        *fileToCompile = (char*)malloc(strlen(mainFile) + 1 + 4); //il + 4 è perche aggiungiamo: ' *.c'
        strcpy(*fileToCompile, mainFile);

        *newTipe = (char*)malloc(strlen(type) + 1);
        strcpy(*newTipe, type);

        sprintf(*fileToCompile, "%s *%s", *fileToCompile, type);
    } else {
        printf("Non esiste un main in questa directory. Nessun tentativo di forzatura possibile. Il parametro '-f' e' stato ignorato\n");
        forceCompilation = 0;
    }
}

//uso: argv[0] file_da_compialare [nome_eseguibile]
int main(int argc, char **argv) {
    char    *fileToCompile = NULL;
    char    *nameExe;
    char    cmd[1024];                                   //qui generiamo il comando per effettuare la compilazione
    char    library[512];
    initArray_str(cmd, 1024);
    initArray_str(library, 512);
    initArray_str(macro, 256);

    language = getLanguage();

    p = argv;                                           //Rendiamo argv globale per semplicità

    analyzeArg(argc, argv);
    managementArg();
    viewServiceState(FALSE);

    initArray_str(library, 512);
    if (linkLibrary)
        readLibrary(library, 512);


    if (countParam == 0) {
        int number_file = search_single_file();
        if (number_file == 1) {
            fileToCompile = (char*)malloc(strlen(uniqueFile) + 1);
            strcpy(fileToCompile, uniqueFile);
            free(uniqueFile);
        } else if (number_file == 0) {
            if (language == ENGLISH)
                printf("No supported file is present in this directory\n");
            else 
                printf("Nessun file supportato presente in questa directory\n");
            exit(EXIT_FAILURE);
        } else {
            if (forceCompilation == 0) {
                if (count_compatible_file(&fileToCompile) == 1) {
                    warningMessage("One compatible file detected\n");
                } else {
                    if (language == ENGLISH) {
                        printf("Specify file name. There are %d files in this directory, among these are compatible:\n", Directory.n_file);
                    } else {
                        printf("Specifica nome file. Sono presenti %d file in questa directory di cui questi compatibili e compilabili:\n", Directory.n_file);
                    }
                    show_source_file();
                    exit(EXIT_FAILURE);
                }
            } else {
                fileToCompile = (char*)malloc(strlen("main.*") + 1);
                strcpy(fileToCompile, "main.*");
            }
        }
    } else {
        if (forceCompilation == 0) {
            fileToCompile = (char*)malloc(strlen(param[0]) + 1);
            strcpy(fileToCompile, param[0]); 
        } else {
            fileToCompile = (char*)malloc(strlen("main.*") + 1);
            strcpy(fileToCompile, "main.*");
        }
    }

    if (debug()) printf("Mi arriva '%s'\n", fileToCompile);
    char *type = (char*)memchr(fileToCompile, '.', strlen(fileToCompile));           	//substring su file_da_compialare sul '.'
    if (type == NULL || !strcmp(type,".")) {
        if (language == ENGLISH)
            printf("[ERROR] The given file [%s] is not a supported source file.\n", fileToCompile);
        else 
            printf("[ERROR] Il file passato [%s] non e' un file sorgente supportato.\n", fileToCompile);
        exit(EXIT_FAILURE);	
    } else if (!strcmp(type, ".*") && forceCompilation == 1) {
        setColor(PRINT_MAGENTA);
        printf("[WARNING] Hai usato il parametro -f che e' cattivo, spietato e anche un po' stupido.\n");
        resetColor();
    }

    if (countParam < 2) {
        printf_d("Nome output di default\n");
        nameExe = (char*)malloc(strlen(fileToCompile) + 1);
        initArray_str(nameExe, strlen(fileToCompile) + 1);
        assign_name(fileToCompile, nameExe);
        if (debug()) printf("\tOvvero: %s\n", fileToCompile);
    } else {
        if (debug())printf("Nome output scelto: %s\n", param[1]);
        nameExe = (char*)malloc(strlen(param[1]) + 1);
        initArray_str(nameExe, strlen(param[1]) + 1);
        strcpy(nameExe, param[1]);
    }

    if (forceCompilation) {
        tryToForce(&fileToCompile, &type);
    }

    create_command(cmd, fileToCompile, compile_to_debug, type, nameExe, library, macro); 
    runCommand(cmd, fileToCompile, compile_to_debug, type, nameExe, library, macro); 

    if (forceCompilation) {
        free(type);
    }
    free(fileToCompile);
    free(nameExe);
    
    if (dummiesMode() && resultCompilation == TRUE) successMessage("Compilation done\n");

    if (resultCompilation == TRUE) exit(EXIT_SUCCESS);
    setColor(PRINT_RED);
    BEGIN_PRINT_RED"Compilation failed\n"END_PRINT;
    exit(EXIT_FAILURE);
}
