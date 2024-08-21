/* *******************************************************
   * @File                 : command.c
   * @Author               : mohamed bahget hamam
   * @Brief                : shell v2.0
   * @gmail                : mahamedhamam15@gmail.com
   *******************************************************
*/


/* **************** Include section start *************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include "command.h"

/* **************** Include section End *************** */

/* **************** Macros section start *************** */


/* **************** Macros section End ****************** */



/* **************** Definition section start *************** */

void Data_IN(char *input , char **args)
{
    int i = 0 ; 
    for ( i = 0 ; i < Max_Arg ; i++)
    {
        args[i] = strsep(&input ," ");
        if (args[i] == NULL ) break;
    }
}

void prompt()
{

    printf("NARUTO :$ ");
}

void pwd (char **args)
{
    if (args == NULL || args[1] == NULL )
    {
        char cwd [1024];
        if (getcwd(cwd , sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }else
        {
            perror("Feh ERROR Hena");
        }
    }else
    {
        printf("error: usage: pwd\n");
    }

}

void echo (char **args)
{
    int i = 0 ; 
    for ( i = 1 ; args[i] != NULL ; i++)
    {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void cp (char **args)
{
    char *source = args[1];
    char *target = args[2];

    if (!source || !target)
    {
        fprintf(stderr , "Usage: cp source target\n");
        return;
    }

    int source_fd = open (source , O_RDONLY);
    if (source_fd < 0 )
    {
        perror ("Feh ERROR Hena");
        return;
    }

    int target_fd ;
    target_fd = open(target , O_WRONLY | O_CREAT | O_EXCL , 0644);
    
    if (target_fd < 0 )
    {
        perror("Feh ERROR Hena");
        close(source_fd);
        return;
    }

    char buffer[1024];
    ssize_t bytes; 
    while ((bytes = read(source_fd , buffer ,sizeof(buffer))) > 0 )
    {
        if (write (target_fd ,buffer , bytes) != bytes)
        {
            perror("Feh ERROR Hena");
            close (source_fd);
            close (target_fd);
            return;
        }    
        if (bytes < 0 )
        {
            perror("Feh ERROR Hena");
        }
        close (source_fd);
        close (target_fd);
    }

}

void mv (char **args)
{
    char *source = args[1];
    char *target = args[2];

    if (!source || !target)
    {
        fprintf(stderr , "Usage: mv source target \n");
        return;
    }
    if (rename(source,target) < 0 )
    {
        perror("Feh ERROR Hena");
    }
}

void help ( char **args)
{
    if (args == NULL || args[1] == NULL)
    {
        printf(">>>NARUTO SHELL HAS SOME BUILT-IN COMMANDS LIKE : \n");
        printf("1 )  pwd        : print the currnet working directory\n");
        printf("2 )  echo       : print a user input string on stdout\n");
        printf("3 )  cp         : copy a file to another file\n");
        printf("4 )  mv         : move a file to another place\n");
        printf("5 )  help       : print all the supported command with a brief info about each one\n");
        printf("6 )  exit       : print \"バイバイ\" and terminate the shell\n");
        printf("7 )  cd         : change the currnet working directory\n");
        printf("8 )  type       : return the type of the command built-in or external or unsupported\n");
        printf("9 )  envir      : print all the environment variables\n");
        printf("10)  phist      : Lists the last 10 processes with their exit status\n");
        printf("11)  free       : print RAM info ( total size, used and free) and Swap area info (total size, used, free)\n");
        printf("12)  uptime     : print the uptime for the system and the time spent in the idle process.\n");
        return;
    }else{};

    if (strcmp(args[1] , "pwd") == 0 )
    { 
        printf("pwd: Print the current working directory\n");
        printf("Usage: pwd\n");

    }else if (strcmp(args[1] , "echo") == 0 )
    {
        printf("echo: print a user input string on stdout\n");
        printf("Usage: echo [your input string]\n");

    }else if (strcmp(args[1] , "cp") == 0 )
    {
        printf("cp: copy a file to another file\n");
        printf("Usage: cp source target\n");

    }else if (strcmp(args[1] , "mv") == 0 )
    {
        printf("mv: move a file to another place\n");
        printf("Usage: mv source target\n");

    }else if (strcmp(args[1] , "exit") == 0 )
    {
        printf("exit: print \"バイバイ\" and terminate the shell\n");
        printf("Usage: exit \n");

    }else if (strcmp(args[1] , "cd") == 0 )
    {
        printf("cd: change the currnet working directory\n");
        printf("Usage: cd [directory] \n");

    }else if (strcmp(args[1] , "type") == 0 )
    {

        printf("type:  return the type of the command built-in or external or unsupported\n");
        printf("Usage: type [command] \n");

    }else if (strcmp(args[1] , "envir") == 0 )
    {
        printf("envir:  print all the environment variables\n");
        printf("Usage: envir [variable] \n");

    }else if (strcmp(args[1] , "phist") == 0 )
    {
        printf("phist:  Lists the last 10 processes with their exit status\n");
        printf("Usage: phist  \n");

    }else if (strcmp(args[1] , "help") == 0 )
    {

        printf("help:  print all the supported command with a brief info about each one\n");
        printf("Usage: help || help [command]  \n");

    }
    else if (strcmp(args[1] , "free") == 0 )
    {

        printf("free:  print RAM info ( total size, used and free) and Swap area info (total size, used, free)\n");
        printf("Usage: free \n");

    }
    else if (strcmp(args[1] , "uptime") == 0 )
    {

        printf("uptime:  print the uptime for the system and the time spent in the idle process.\n");
        printf("Usage: uptime \n");

    }else
    {
        printf("%s is not a supported command, plz enter 'help' to know the supported commands\n" , args[1]);
    }
}


int myexit (char **args)
{   
    if (args == NULL || args[1] == NULL)
    {
        printf("バイバイ\n");
        exit(0);
        return 0 ;
    }else
    {
        printf("error: usage: exit\n");
    }

}

int cd ( char **args)
{
    if ( args[1] == NULL)
    {
        fprintf(stderr , "cd: expected argument to \"cd\"\n");
    }else if (chdir(args[1]) != 0 )
    {
        perror("cd error");
    }else{};
    return 1 ;
}

int is_external(const char *command) {
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        return 0;
    }
   
    char *path_env_copy = strdup(path_env);
    if (path_env_copy == NULL) {
        perror("strdup");
        return 0;
    }

    
    char *dir = strtok(path_env_copy, ":");
    while (dir != NULL) {
        
        char command_path[1024];
        snprintf(command_path, sizeof(command_path), "%s/%s", dir, command);
        
        
        struct stat st;
        if (stat(command_path, &st) == 0 && (st.st_mode & S_IXUSR)) {
            free(path_env_copy);
            return 1; 
        }

        dir = strtok(NULL, ":");
    }

    free(path_env_copy);
    return 0;
}

int type (char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr , "type: expected argument to 'type' \n");
        return 1 ;

    }
    const char *built_in_commands[]={"cp", "mv" , "pwd" , "echo" , "help" , "exit" , "cd" , "type" , "envir" , "phist" , "free" , "uptime"};
    size_t num_built_in = sizeof(built_in_commands)/sizeof(built_in_commands[0]);
    ssize_t i = 0 ;
    for ( i = 0 ; i < num_built_in ;i++)
    {
        if (strcmp(args[1] , built_in_commands[i]) == 0 )
        {
            printf("'%s' is a shell built-in command\n" , args[1]);
            return 1; 
        }
    }
    if (is_external(args[1]))
    {
        printf("'%s' is an external command\n" , args[1]);
    }else
    {
        printf("'%s' is an unsupported command\n", args[1]);
    }
    return 1 ;
}

int envir (char **args)
{
    if (args[1] == NULL)
    {
        extern char **environ;
        for (char **env = environ; *env != NULL; env++) 
        {
            printf("%s\n", *env);
        }
    } else
    {
        char *value = getenv(args[1]);
        if (value != NULL) 
        {
            printf("%s\n", value);
        } else 
        {
            printf("%s: No such environment variable\n", args[1]);
        }
    }
    return 1 ; 
}
typedef struct 
{
    int status;
    pid_t pid;
} process_info;

process_info process_history[MAX_HISTORY];

int history_index = 0;

int phist (char **args)
{
    for (int i = 0; i < MAX_HISTORY; i++) 
    {
        if (process_history[i].pid != 0) 
        {
            printf("PID: %d, Exit Status: %d\n", process_history[i].pid, process_history[i].status);
        }
    }
    return 1 ;
}

void add_to_history(pid_t pid, int status)
{
    process_history[history_index].pid = pid;
    process_history[history_index].status = status;
    history_index = (history_index + 1) % MAX_HISTORY;
}

void free_command()
{
    FILE *file = fopen("/proc/meminfo" ,"r");
    if (file == NULL)
    {
        perror("failed to open /proc/meminfo");
        return;
    }
    char line[256];
    while (fgets(line , sizeof(line) , file))
    {
        printf("%s" , line);
    }
    fclose(file);
}

void uptime_command()
{
    FILE *file = fopen("/proc/uptime" , "r");
    if (file == NULL)
    {
        perror("failed to open /proc/uptime");
        return;
    }
    char line[256];
    fgets(line , sizeof(line) , file);
    printf("uptime: %s" , line);
    fclose(file);
}


void handle_piping(char **args) 
{
    int pipefd[2];
    pid_t p1, p2;
    int i = 0;

   
    while (args[i] != NULL && strcmp(args[i], "|") != 0)
    {
        i++;
    }

    if (args[i] == NULL) 
    {
        
        return;
    }

    args[i] = NULL; 

    if (pipe(pipefd) < 0) 
    {
        perror("Pipe failed");
        return;
    }

    p1 = fork();
    if (p1 < 0) 
    {
        perror("Fork failed");
        return;
    }

    if (p1 == 0) 
    {
        
        close(pipefd[0]);       
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]);

        if (execvp(args[0], args) < 0) 
        {
            perror("Execution failed");
            exit(1);
        }
    } else 
    {
        p2 = fork();
        if (p2 < 0) 
        {
            perror("Fork failed");
            return;
        }

        if (p2 == 0) 
        {
            
            close(pipefd[1]);    
            dup2(pipefd[0], STDIN_FILENO); 
            close(pipefd[0]);

            if (execvp(args[i + 1], args + i + 1) < 0) 
            {
                perror("Execution failed");
                exit(1);
            }
        } else 
        {
            
            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            wait(NULL);
        }
    }
}

void handle_redirection(char **args) 
{
    int i = 0;
    int fd;
    int append_mode = 0; 

    while (args[i] != NULL) {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) 
        {
            if (args[i + 1] == NULL) {
                fprintf(stderr, "No file specified for redirection\n");
                return;
            }

            if (strcmp(args[i], ">>") == 0) 
            {
                append_mode = 1;
            }

            
            if (append_mode) 
            {
                fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            } else {
                fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }

            if (fd < 0) 
            {
                perror("Failed to open file for redirection");
                return;
            }

            dup2(fd, STDOUT_FILENO); 
            close(fd);
            args[i] = NULL; 
            break;
        } else if (strcmp(args[i], "<") == 0) 
        {
            if (args[i + 1] == NULL) 
            {
                fprintf(stderr, "No file specified for input redirection\n");
                return;
            }

            fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) 
            {
                perror("Failed to open file for input redirection");
                return;
            }

            dup2(fd, STDIN_FILENO); 
            close(fd);
            args[i] = NULL; 
            break;
        }
        i++;
    }
}


/* ************** Definition section End ************************ */



/* *******************************************************
   @User                 @Date               @time 
   *******************************************************
   mohamed hamam         31july2024          1:22pm
   mohamed hamam         2 aug 2024          4:50pm

*/

