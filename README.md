# Minishell - @42Wolfsburg

As beautiful as a shell

## About

Minishell is one of 3 projects about Unix in 3rd Circle at 42.
It's a minimum viable version of a real shell.
The main goal is to have a good understanding of input parsing, tokenization, process creation and
synchronisation using the C programmming language.

## Installation & Usage

### Requirements
The only requirements are:
- GNU make (v3.81)
- GCC (12.0.0) (clang-1200.0.32.28)

Those versions are the ones used during development.

### Building the program

1. Download/Clone this repo

        git clone https://github.com/qduong42/42_Minishell.git
2. `cd` into the root directory and run `make`

        cd minishell
        make

### Running the program

After running make, execute `./minishell` from the project root.

## Main Project Instructions

### Mandatory

- Only use C
- Must respect the 42 imposed coding style The Norminator
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage the errors using perror or custom suitable error message
to the error output
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Must have a Makefile to build the program
- The binary file must be named `minishell`
- Can use Libft
- Handle program interruption (Ctrl + D)

### Bonuses

- Nested quotes feat. overengineered madness


## Notes

- Some functions are commented for ease of understanding
- There are probably better ways to implement it, we are limited by a set of functions at 42. (Limitation ensures that we have a deeper understanding of what is going on behind the hood), please review the project instructions before you explain how `X` or `Y` would have been a better way to do it ;)


Enjoy!

