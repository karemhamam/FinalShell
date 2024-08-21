/* *******************************************************
   * @File                 : My_shell.c
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
#include <libgen.h>
#include <sys/wait.h>
#include "command.h"
/* **************** Include section End *************** */

/* **************** macros section start *************** */


/* **************** macros section End *************** */




int main() 
{
    char input[MAX_INPUT_LENGTH];
    char *args[Max_Arg];
    int running = 1;

    while (running)
    {
        prompt();
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) 
        {
            break;
        }

        
        input[strcspn(input, "\n")] = 0;

        Data_IN(input, args);

        if (args[0] == NULL) 
        {
            continue;
        }

        
        handle_piping(args);
        handle_redirection(args);

        if (strcmp(args[0], "pwd") == 0) 
        {
            pwd(args);

        } else if (strcmp(args[0], "echo") == 0) 
        {
            echo(args);
        } else if (strcmp(args[0], "cp") == 0) 
        {
            cp(args);
        } else if (strcmp(args[0], "mv") == 0) 
        {
            mv(args);
        } else if (strcmp(args[0], "help") == 0) 
        {
            help(args);
        } else if (strcmp(args[0], "exit") == 0) 
        {
            running = myexit(args);
        } else if (strcmp(args[0], "cd") == 0) 
        {
            running = cd(args);
        } else if (strcmp(args[0], "type") == 0) 
        {
            running = type(args);
        } else if (strcmp(args[0], "envir") == 0) 
        {
            running = envir(args);
        } else if (strcmp(args[0], "phist") == 0) 
        {
            running = phist(args);
        }else if (strcmp(args[0] , "free") == 0)
        {
            free_command();

        }else if (strcmp(args[0] , "uptime") == 0 )
        {
            uptime_command();

        }else if (is_external(args[0])) 
        {
            pid_t pid = fork();
            if (pid == 0) 
            {
                execvp(args[0], args);
                perror("Execution failed");
                exit(1);
            } else if (pid < 0) 
            {
                perror("Fork failed");
            } else 
            {
                wait(NULL);
            }
        }else 
        {
            printf("'%s' is not a recognized command\n", args[0]);
        }
    }

    return 0;
}



/* **************** Definition section start *************** */



/* ************** Definition section End *************** */



/* *******************************************************
   @User                 @Date             @time
   *******************************************************
   mohamed hamam         31july2024         1:22 pm
   mohamed hamma         2 aug 2024         4:50 pm

*/

