
# 🐚 Simple Shell
### Everything you need to know to start coding your own shell

## 📌 Description

This project consists of creating a **minimal Unix shell** that behaves like /bin/sh for basic functionalities. The shell reads commands from the standard input, parses them, and executes them using system calls.

## What is a Shell?

A shell is a command-line interpreter that provides a user interface for interacting with the operating system. It:

- Displays a prompt
- Reads user input
- Parses commands and arguments
- Executes programs
- Handles errors

**Examples of shells:**

- /bin/sh
- bash
- zsh
----------

## ⚙️ Project Requirements
#### Allowed Functions

- All functions from string.h
- System calls and functions such as:

    * fork, execve, wait, waitpid
    * read, write, open, close

- getline, malloc, free
- access, stat, chdir
- perror, printf, fprintf

### Compilation
```c
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
### Constraints

- No memory leaks
- Code must follow Betty style
- The shell must handle errors gracefully
----------

## 🔄 How the Shell Works (High Level)

    1. Display a prompt

    2. Read input from stdin

    3. Parse the command and arguments

    4. Check if the command exists

    5. Create a child process using fork

    6. Execute the command using execve

    7. Parent process waits for the child
----------
### Flow Diagram (Simplified)
```c
Prompt → Read → Parse → Fork → Exec → Wait → Prompt
```
## 🌱 Environment Variables

**The environment is accessed using:**
```c
extern char **environ;
```
- ```environ``` is a double pointer (```char **```)
- Each entry is of the form ```NAME=VALUE```
- Used by ```execve``` to pass environment variables
----------

## 🧭 Path Resolution

**If the command is not an absolute path, the shell:**

- Retrieves the ```PATH``` variable
- Splits it using ```:```
- Checks each directory with ```access()```

#### Example:
```c
/bin/ls
/usr/bin/ls
```
----------

## 🧩 Built-in Commands

Built-ins are commands executed **without creating a new process**.

**Required built-ins:**

- ```exit```– exits the shell
- ```env``` – prints the environment

**Optional built-ins:**

- ```cd```
- ```setenv```
- ```unsetenv```
----------

## ❌ Error Handling

- Use perror() for system errors
- Display meaningful messages
- Handle command not found errors

#### Example:
```c
hsh: command not found
```
----------

## 🧠 Memory Management

- lways free() allocated memory
- Avoid memory leaks
 Use tools like valgrind
----------

## 🚀 Example Usage
```c
$ ./hsh
$ ls -l
$ /bin/echo Hello
$ exit
```
----------

## 📁 Files Structure (Example)
```c
.
├── main.c
├── shell_loop.c
├── parse.c
├── execute.c
├── path.c
├── builtins.c
├── utils.c
├── shell.h
└── README.md
$ exit
```
----------
## 🎯 Learning Objectives

**By completing this project, you will understand:**

- How a shell works internally
- Process creation and execution
- System calls in Unix
- Environment handling
- Memory management in C