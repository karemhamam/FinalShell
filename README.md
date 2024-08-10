# Custom Shell - Version 3

## Overview
This custom shell is designed to mimic some of the functionalities of a Unix-like command line interface. It supports internal and external commands, input/output redirection, piping, and manages both environment and local variables.


## Features

- **Custom Commands**: Execute custom shell commands inspired by Naruto characters.
- **File Operations**: Copy and move files with ease.
- **Environment Management**: Print environment variables and change directories.
- **Process Tracking**: List the last 10 processes with their exit statuses.
- **Command Information**: Get information about built-in, external, and unsupported commands.
- **fix some errrors** : fix the combined commnad error, and examples of the output.

### Internal Commands

1. **pwd**: Print the current working directory.
   - Usage: `pwd`

2. **echo**: Print a user input string on stdout.
   - Usage: `echo [your input string]`

3. **cp**: Copy a file to another file.
   - Usage: `cp source target`

4. **mv**: Move a file to another place.
   - Usage: `mv source target`

5. **help**: Print all the supported commands with a brief info about each one.
   - Usage: `help`

6. **myexit**: Print "バイバイ" and terminate the shell.
   - Usage: `myexit`

7. **cd**: Change the current working directory.
   - Usage: `cd [directory]`

8. **type**: Return the type of the command (built-in, external, or unsupported).
   - Usage: `type [command]`

9. **envir**: Print all the environment variables.
   - Usage: `envir`

10. **phist**: Lists the last 10 processes with their exit status.
    - Usage: `phist`

11. **free**: print RAM info ( total size, used and free) and Swap area info (total size, used, free)
    - Usage: `free`

12. **uptime**: print the uptime for the system and the time spent in the idle process.
    - Usage: `uptime`

### External Commands
Any command available in the PATH environment variable can be executed as an external command.

### Shell Features
- **Redirection**: Support for input (`<`), output (`>`, `>>`), and error (`2>`, `2>>`) redirection.
- **Piping**: Support for piping between two processes (`|`).

## Installation

1. Clone the repository and compile the code:  git clone ()

## Compilation

To compile the shell program, use the following command:

 gcc -o myShell My_shell.c command.c

## Usage

To use the shell, compile the source code and run the executable. You can then type any of the supported commands to perform the corresponding actions.

## Contributing

Contributions are welcome! 
If you have suggestions for new features or improvements, feel free to open an issue or submit a pull request.

## License

mahamedhamam15@gmail.com

