# holbertonschool-simple_shell
## Description

This project is a basic simple shell written in C that interprets and executes user commands from the standard input. We will be working together as a team on different branches for simple shell.

## Tasks

0. README, man, AUTHORS
1. Betty would be proud
2. Simple shell 0.1
3. Simple shell 0.2
4. Simple shell 0.3
5. Simple shell 0.4
6. Simple shell 1.0

## Installation
To compile the code:

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

## Usage
Run the shell with:

`./hsh`

Interactive mode:

```
$ ./hsh
$ ls -l
$ exit
```

Non-interactive mode:

```
echo "ls -l | ./hsh
./hsh < commands.txt
```

## Features

1. Executes commands with arguments
2. Supports built-in commands like exit, env, etc.
3. Handles command path resolution using PATH
4. Input parsing (tokenization)
5. Forks and executes commands
6. Handles EOF (Ctrl+D) and signals (like Ctrl+C)

## Built-in Commands

`exit` Exits the shell
`env` Prints enviroment variables

## Format Specifiers

`%s` String (used to print command names or arguments)
`%d/%i` Signed integer (used for status codes or loop counters)
`%c` Character (used to print a single character)
`%u` Unsigned int (e.g., for PID or return codes)
`%%` Literal % character

These are mainly used in the shell for debugging, error messages, or custom prompts/logs

## Example

```
$ ./hsh
$ echo Hello, Shell!
Hello, Shell!
$ ls
file1.c file2.c README.md
$ exit
```

## AUTHORS

- <a href="https://github.com/LuvliNay" target="_blank">Nayshka Oliveras</a>
- <a href="https://github.com/HectorPR4546" target="_blank">Hector Perez</a>

# Contributing

*Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.*

## License

_Please notify us for permission to use this code._
