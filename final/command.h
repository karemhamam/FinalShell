
#ifndef COMMAND_H
#define COMMAND_H

#define MAX_INPUT_LENGTH 1024
#define Max_Arg       (128)
#define MAX_HISTORY    (10)

void prompt();
void Data_IN(char *input , char **args);
void pwd(char **args);
void echo (char **args);
void cp (char **args);
void mv (char **args);
void help ( char **args);

void handle_piping(char **args);
void handle_redirection(char **args);
void free_command();
void uptime_command();

int myexit (char **args);
int cd ( char **args);
int type (char **args);
int phist (char **args);
int envir (char **args);
int is_external(const char *command);




#endif

