#ifndef COMPILE_H
#define COMPILE_H

#define PATH_FILE_LIBRARY           "/home/%s/.compile_lib.txt"
#define INIT_LIBRARY                "-lpthread -lm -lrt"
#define INITIALIZE_STATE_SERVICE    "tttt"                       /*yes view generate command | advanced mode | yes english package | yes ia  */
#define ITALIAN                     1
#define ENGLISH                     2
#define VERSION                     "V. 5.4 KNIGHTS IA "            /*old version are not available*/

#define DISABLE_JAVA                ".java-SUPPORT_FINISHED"
//#define DISABLE_JAVA                ".java"    /*support for java source is finished, if you would try to use remove '-SUPPORT_FINISHED'. Use is ABSOLUTELY NO WARRANTY*/

/*
 * Globale variable
 *
*/
char    **p;
int     compile_to_debug = 0;
int     forceCompilation = 0;
int     linkLibrary = 0;
int     howColor = 0;
int     enableCompilationAttempts = TRUE;
char    macro[256];
int     resultCompilation  = FALSE;
int     language = ENGLISH;
int     enableAutoExe = TRUE;


/*
 * Prototype
*/
static inline void create_command(char *cmd, char *fileToCompile, int compile_to_debug, char *type, char *name_output, char *library, char *macro) __attribute__((always_inline));

void    managementCommand(int index);
int     compilationSuccessful();
void    runCommand(char *cmd, char *fileToCompile, int compile_to_debug, char *type, char *name_output, char *library, char *macro);
void    managementArg();
int     tryToForce(char **fileToCompile, char **newTipe);
void    readLibrary(char *lib, int dim);
int     addLibrary(char *param);
void    addMacro(char *mcr);
void    addMacro(char *mcr);
void    printCommand(char *cmd, char *fileToCompile, char *library, char *_macro, char *name_output);
void    showCommand(char *cmd, char *fileToCompile, char *library, char *name_output);
void    setFileSystem(int param, char newSet);
int     dummiesMode();
int     managementModifySetting(char *command);
int     search_single_file();
void    print_syntax(char **argv);
void    disableCompilationAttempts();
void    active_dtd();
void    active_d();
void    show_error_much_file();
void    writeIntoFileCommand(char *cmd);
void    removeRegister();
void    viewRegister();
void    changePredefiniteEditor();
void    managementParam(int index);
void    abortProgramm(char *nameCommand);
int     setLanguage();
void    viewServiceState(int force);

#endif
