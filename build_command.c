#ifndef BUILD_COMMAND
#define BUILD_COMMAND


int containMainFunction(char *nameFile) {
    FILE *f = fopen(nameFile, "r");     //esiste sicuramente
    char row[256];
    initArray_str(row, 256);
    while (fgets(row, 256, f) > 0) {
        if (strstr(row, "int main")) {
            fclose(f);
            return TRUE;
        }
        initArray_str(row, 256);
    }
    fclose(f);
    return FALSE;
} 

//Aggiunge una o piu' macro passate come parametro/i in compilazione
void addMacro(char *mcr) {
    sprintf(macro, "%s -D%s ", macro, mcr);
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
        if (!strcmp(type, ".c") || !strcmp(type, ".c++") || !strcmp(type, ".cpp") || !strcmp(type, DISABLE_JAVA) || !strcmp(type, ".cc")) {
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

void disableCompilationAttempts() {
    enableCompilationAttempts = FALSE;
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

    getUserId(user, TRUE);
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        sprintf(cwd, "%s",strerror(errno)); //get path
    }

    sprintf(path, "/home/%s/.compile_lastCommand.txt", user);

    sprintf(text, "%s \t\tgenerated at: %s\t\ton %s\n", cmd, getTime(), cwd);

    writeFile(path, text, "a+");

    return;
}

void removeRegister() {     //registro delle compilazioni
    char user[32];
    char path[128];
    initArray_str(user, 32);
    initArray_str(path, 128);

    getUserId(user, TRUE);


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

    getUserId(user, TRUE);

    sprintf(path, "/home/%s/.compile_lastCommand.txt", user);
    sprintf(cmd, "editor %s", path);
    system(cmd);                                        //apri l'editor predefinito e permettimi di modificare il file
}

void managementParam(int index) {
    //nothing to do 
}

#endif
