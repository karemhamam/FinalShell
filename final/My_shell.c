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
#include "command.h"
/* **************** Include section End *************** */

/* **************** macros section start *************** */


/* **************** macros section End *************** */



int main()
{
    char input[Max_Data_Size];
    char *args[Max_Arg];
    const char *naruto = 
    "\n"
    "███▄▄▄▄      ▄████████    ▄████████ ███    █▄      ███      ▄██████▄   \n"
    "███▀▀▀██▄   ███    ███   ███    ███ ███    ███ ▀█████████▄ ███    ███  \n"
    "███   ███   ███    ███   ███    ███ ███    ███    ▀███▀▀██ ███    ███  \n"
    "███   ███   ███    ███  ▄███▄▄▄▄██▀ ███    ███     ███   ▀ ███    ███  \n"
    "███   ███ ▀███████████ ▀▀███▀▀▀▀▀   ███    ███     ███     ███    ███  \n"
    "███   ███   ███    ███ ▀███████████ ███    ███     ███     ███    ███  \n"
    "███   ███   ███    ███   ███    ███ ███    ███     ███     ███    ███  \n"
    " ▀█   █▀    ███    █▀    ███    ███ ████████▀     ▄████▀    ▀██████▀   \n";
    printf("%s", naruto);
    while (1)
    {
        prompt();
        if (fgets(input , Max_Data_Size , stdin) == NULL)
        {
            perror("Feh ERROR Hena");
            continue;
        }   
        
        input[strcspn(input,"\n")] = 0 ;

        if (strcmp (input , "") == 0 ) continue;
        Data_IN(input, args);
        handle_redirection(args);
        if (strcmp (args[0],"pwd") == 0)
        {
            pwd(args);
        }else if (strcmp (args[0] , "echo") == 0)
        {
            echo(args);
        }else if (strcmp (args[0], "cp") == 0 )
        {
            cp(args);
        }else if (strcmp (args[0], "mv") == 0 )
        {
            mv(args);
        }else if (strcmp (args[0] , "exit") == 0)
        {
            myexit(args);
        }else if ( strcmp (args[0], "help") == 0 )
        {
            help(args);
        }else if ( strcmp (args[0], "cd") == 0 )
        {
            cd(args);

        }else if ( strcmp (args[0], "type") == 0 )
        {
            type(args);

        }else if ( strcmp (args[0], "envir") == 0 )
        {
            envir(args);

        }else if ( strcmp (args[0] , "phist") == 0)
        {
            phist(args);
        }
        else if ( strcmp (args[0] , "free") == 0)
        {
            free_command();
        }
        else if ( strcmp (args[0] , "uptime") == 0)
        {
            uptime_command();
        }
        else
        {
            handle_piping(args);
        }
    }


  return 0 ;
}


/* **************** Definition section start *************** */



/* ************** Definition section End *************** */



/* *******************************************************
   @User                 @Date             @time
   *******************************************************
   mohamed hamam         31july2024         1:22 pm
   mohamed hamma         2 aug 2024         4:50 pm

*/

