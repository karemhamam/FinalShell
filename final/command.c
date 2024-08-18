/* *******************
   * @File                 : command.c
   * @Author               : mohamed bahget hamam
   * @Brief                : shell v2.0
   * @gmail                : mahamedhamam15@gmail.com
   *******************
*/

/* ****** Include section start ***** */

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

/* ****** Include section End ***** */

/* ****** Definition section start ***** */

void Data_IN(char *input, char **args)
{
    int i = 0;
    for (i = 0; i < Max_Arg; i++)
    {
        args[i] = strsep(&input, " ");
        if (args[i] == NULL)
            break;
    }
}

void prompt()
{
    printf("NARUTO :$ ");
}

void pwd(char **args)
{
    if (args == NULL || args[1] == NULL)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("Feh ERROR Hena");
        }
    }
    else
    {
        printf("error: usage: pwd\n");
    }
}

void echo(char **args)
{
    int i = 0;
    for (i = 1; args[i] != NULL; i++)
    {
        printf("%s ", args[i]);
    }
    printf("\n");
}

void cp(char **args)
{
    char *source = args[1];
    char *target = args[2];

    if (!source || !target)
    {
        fprintf(stderr, "Usage: cp source target\n");
        return;
    }

    int source_fd = open(source, O_RDONLY);
    if (source_fd < 0)
    {
        perror("Feh ERROR Hena");
        return;
    }

    int target_fd;
    target_fd = open(target, O_WRONLY | O_CREAT | O_EXCL, 0644);

    if (target_fd < 0)
    {
        perror("Feh ERROR Hena");
        close(source_fd);
        return;
    }

    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(source_fd, buffer, sizeof(buffer))) > 0)
    {
        if (write(target_fd, buffer, bytes) != bytes)
        {
            perror("Feh ERROR Hena");
            close(source_fd);
            close(target_fd);
            return;
        }
    }
    if (bytes < 0)
    {
        perror("Feh ERROR Hena");
    }
    close(source_fd);
    close(target_fd);
}

void mv(char **args)
{
    char *source = args[1];
    char *target = args[2];

    if (!source || !target)
    {
        fprintf(stderr, "Usage: mv source target \n");
        return;
    }
    if (rename(source, target) < 0)
    {
        perror("Feh ERROR Hena");
    }
}

void help(char **args)
{
    if (args == NULL || args[1] == NULL)
    {
        printf(">>>NARUTO SHELL HAS SOME BUILT-IN COMMANDS LIKE : \n");
        printf("1 )  pwd        : print the current working directory\n");
        printf("2 )  echo       : print a user input string on stdout\n");
        printf("3 )  cp         : copy a file to another file\n");
        printf("4 )  mv         : move a file to another place\n");
        printf("5 )  help       : print all the supported command with a brief info about each one\n");
        printf("6 )  exit       : print \"バイバイ\" and terminate the shell\n");
        printf("7 )  cd         : change the current working directory\n");
        printf("8 )  type       : return the type of the command built-in or external or unsupported\n");
        printf("9 )  envir      : print all the environment variables\n");
        printf("10)  phist      : Lists the last 10 processes with their exit status\n");
        printf("11)  free       : print RAM info ( total size, used and free) and Swap area info (total size, used, free)\n");
        printf("12)  uptime     : print the uptime for the system and the time spent in the idle process.\n");
        return;
    }
    else
    {
    };

    if (strcmp(args[1], "pwd") == 0)
    {
        printf("pwd: Print the current working directory\n");
        printf("Usage: pwd\n");
    }
    else if (strcmp(args[1], "echo") == 0)
    {
        printf("echo: print a user input string on stdout\n");
        printf("Usage: echo [your input string]\n");
    }
    else if (strcmp(args[1], "cp") == 0)
    {
        printf("cp: copy a file to another file\n");
        printf("Usage: cp source target\n");
    }
    else if (strcmp(args[1], "mv") == 0)
    {
        printf("mv: move a file to another place\n");
        printf("Usage: mv source target\n");
    }
    else if (strcmp(args[1], "exit") == 0)
    {
        printf("exit: print \"バイバイ\" and terminate the shell\n");
        printf("Usage: exit \n");
    }
    else if (strcmp(args[1], "cd") == 0)
    {
        printf("cd: change the current working directory\n");
        printf("Usage: cd [directory] \n");
    }
    else if (strcmp(args[1], "type") == 0)
    {
        printf("type:  return the type of the command built-in or external or unsupported\n");
        printf("Usage: type [command] \n");
    }
    else if (strcmp(args[1], "envir") == 0)
    {
        printf("envir:  print all the environment variables\n");
        printf("Usage: envir [variable] \n");
    }
    else if (strcmp(args[1], "phist") == 0)
    {
        printf("phist:  Lists the last 10 processes with their exit status\n");
        printf("Usage: phist  \n");
    }
    else if (strcmp(args[1], "help") == 0)
    {
        printf("help:  print all the supported command with a brief info about each one\n");
        printf("Usage: help || help [command]  \n");
    }
    else
    {
        printf("%s is not a supported command, please enter 'help' to know the supported commands\n", args[1]);
    }
}

int myexit(char **args)
{
    if (args == NULL || args[1] == NULL)
    {
        printf("バイバイ\n");
        exit(0);
        return 0;
    }
    else
    {
        printf("error: usage: exit\n");
    }
}

int cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "cd: expected argument to \"cd\"\n");
    }
    else if (chdir(args[1]) != 0)
    {
        perror("cd error");
    }
    else
    {
    };
    return 1;
}

int is_external(const char *command)
{
    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        return 0;
    }

    char *path_env_copy = strdup(path_env);
    if (path_env_copy == NULL)
    {
        perror("strdup");
        return 0;
    }

    char *dir = strtok(path_env_copy, ":");
    while (dir != NULL)
    {
        char command_path[1024];
        snprintf(command_path, sizeof(command_path), "%s/%s", dir, command);

        struct stat st;
        if (stat(command_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_env_copy);
            return 1;
        }

        dir = strtok(NULL, ":");
    }

    free(path_env_copy);
    return 0;
}

int type(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "type: expected argument to 'type' \n");
        return 1;
    }
    const char *command = args[1];
    if (strcmp(command, "pwd") == 0 || strcmp(command, "echo") == 0 || strcmp(command, "cp") == 0 ||
        strcmp(command, "mv") == 0 || strcmp(command, "help") == 0 || strcmp(command, "exit") == 0 ||
        strcmp(command, "cd") == 0 || strcmp(command, "type") == 0 || strcmp(command, "envir") == 0 ||
        strcmp(command, "phist") == 0)
    {
        printf("%s is a built-in command\n", command);
    }
    else if (is_external(command))
    {
        printf("%s is an external command\n", command);
    }
    else
    {
        printf("%s is an unsupported command\n", command);
    }
    return 0;
}

#define MAX_HISTORY 10

typedef struct
{
    pid_t pid;
    int status;
} ProcessInfo;

ProcessInfo history[MAX_HISTORY];
int history_count = 0;

void add_to_history(pid_t pid, int status)
{
    if (history_count < MAX_HISTORY)
    {
        history[history_count].pid = pid;
        history[history_count].status = status;
        history_count++;
    }
    else
    {
        for (int i = 1; i < MAX_HISTORY; i++)
        {
            history[i - 1] = history[i];
        }
        history[MAX_HISTORY - 1].pid = pid;
        history[MAX_HISTORY - 1].status = status;
    }
}

int phist(char **args)
{
    printf("Last %d processes:\n", MAX_HISTORY);
    for (int i = 0; i < history_count; i++)
    {
        printf("PID: %d, Status: %d\n", history[i].pid, history[i].status);
    }
    return 0;
}

int envir(char **args)
{
    extern char **environ;
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}

void handle_piping(char **args)
{
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1)
    {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        return;
    }

    if (pid1 == 0)
    {
        close(pipe_fds[0]);
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[1]);
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        return;
    }

    if (pid2 == 0)
    {
        close(pipe_fds[1]);
        dup2(pipe_fds[0], STDIN_FILENO);
        close(pipe_fds[0]);
        execvp(args[2], args + 2);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    close(pipe_fds[0]);
    close(pipe_fds[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void handle_redirection(char **args)
{
    int in_fd = -1, out_fd = -1;
    char *input_file = NULL, *output_file = NULL;

    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            input_file = args[i + 1];
            args[i] = NULL;
        }
        else if (strcmp(args[i], ">") == 0)
        {
            output_file = args[i + 1];
            args[i] = NULL;
        }
    }

    if (input_file)
    {
        in_fd = open(input_file, O_RDONLY);
        if (in_fd < 0)
        {
            perror("open input file");
            return;
        }
    }

    if (output_file)
    {
        out_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd < 0)
        {
            perror("open output file");
            if (in_fd >= 0)
                close(in_fd);
            return;
        }
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        if (in_fd >= 0)
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd >= 0)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    if (in_fd >= 0)
        close(in_fd);
    if (out_fd >= 0)
        close(out_fd);

    int status;
    waitpid(pid, &status, 0);
    add_to_history(pid, status);
}

void free_command()
{
    FILE *fp;
    char path[1035];

    fp = popen("free -h", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path) - 1, fp) != NULL)
    {
        printf("%s", path);
    }

    pclose(fp);
}

void uptime_command()
{
    FILE *fp;
    char path[1035];

    fp = popen("uptime -p", "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path) - 1, fp) != NULL)
    {
        printf("%s", path);
    }

    pclose(fp);
}
