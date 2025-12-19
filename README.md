
# 🐚 Simple Shell (hsh)
**Language:** C

**Coding style:** Betty

**Platform:** Ubuntu 20.04

**Goal:** Minimal UNIX shell compliant with standard /bin/sh behavior

**Quality:** Memory-safe (no memory leaks)

---

## 📖 Table of Contents

    1. Introduction
    2. Project Objectives
    3. Flowchart
    4. Project Structure
    5. Compilation and Manual Page
    6. Usage Examples
    7. Features
    8. Constraints
    9. Sources and References

---

## 📌 Description

**Simple Shell** is a minimalist UNIX command interpreter written in **C**.
It reproduces the basic behavior of a standard shell such as `/bin/sh` for common use cases.

This project was developed as part of the **Holberton School** curriculum to gain a deeper understanding of how shells work internally, including process creation, command parsing, execution, and environment handling.

The shell reads user input, parses commands, searches for executables in the `PATH`, and executes them using system calls such as `fork`, `execve`, and `wait`.
For standard use cases, its behavior is intended to be consistent with `/bin/sh`.

---

## ✅ Project Objectives

**The main objectives of this project are to:**
- Implement a **minimal UNIX shell** in C
- Support both **interactive** and **non-interactive** modes
- Understand **process creation and management**
- Parse user input into executable commands
- Execute commands using low-level system calls
- Implement basic **built-in commands**
- Ensure **strict compliance with the Betty coding standard**
- Guarantee **safe memory management** (no leaks)

---

## 🔁 Flowchart
<img src="assets/image/Flowchart_Shell.webp" alt="Flowchart Shell" width="600">
**The shell follows this general execution flow:**

* Display a prompt in interactive mode
* Read user input using `getline`
* Remove the trailing newline and tokenize the command
* Check for built-in commands
* Search for the command in the `PATH`
* Create a child process using `fork`
* Execute the command using `execve`
* Wait for the child process to terminate

---

## 🧠 Allowed Functions and System Calls

This project strictly uses **only the functions and system calls authorized by the Holberton School project specification**.
No other functions, libraries, or system calls are used.

#### ✔️ Authorized functions

- All functions from `string.h`
- `access` *(man 2 access)*
- `chdir` *(man 2 chdir)*
- `close` *(man 2 close)*
- `closedir` *(man 3 closedir)*
- `execve` *(man 2 execve)*
- `exit` *(man 3 exit)*
- `_exit` *(man 2 _exit)*
- `fflush` *(man 3 fflush)*
- `fork` *(man 2 fork)*
- `free` *(man 3 free)*
- `getcwd` *(man 3 getcwd)*
- `getline` *(man 3 getline)*
- `getpid` *(man 2 getpid)*
- `isatty` *(man 3 isatty)*
- `kill` *(man 2 kill)*
- `malloc` *(man 3 malloc)*
- `open` *(man 2 open)*
- `opendir` *(man 3 opendir)*
- `perror` *(man 3 perror)*
- `printf` *(man 3 printf)*
- `fprintf` *(man 3 fprintf)*
- `vfprintf` *(man 3 vfprintf)*
- `sprintf` *(man 3 sprintf)*
- `putchar` *(man 3 putchar)*
- `read` *(man 2 read)*
- `readdir` *(man 3 readdir)*
- `signal` *(man 2 signal)*
- `stat` / `__xstat` *(man 2 stat)*
- `lstat` / `__lxstat` *(man 2 lstat)*
- `fstat` / `__fxstat` *(man 2 fstat)*
- `strtok` *(man 3 strtok)*
- `wait` *(man 2 wait)*
- `waitpid` *(man 2 waitpid)*
- `wait3` *(man 2 wait3)*
- `wait4` *(man 2 wait4)*
- `write` *(man 2 write)*

---

## ⚙️ Compilation

**Compile the shell using gcc:**
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
---

## ▶️ Testing
#### Interactive mode

**Your shell should work properly in interactive mode:**
```bash
julien@ubuntu:/# ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
julien@ubuntu:/#
```
**In this mode, the shell:**
- Displays a prompt
- Waits for user input
- Executes commands
- Exits cleanly when exit is entered

---
### Non-interactive mode

Your shell must also work in **non-interactive mode**, receiving input from standard input:
```bash
julien@ubuntu:/# echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
```
**It should correctly handle input from files and pipes:**
```bash
julien@ubuntu:/# cat test_ls_2
/bin/ls
/bin/ls

julien@ubuntu:/# cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
```
---

## ✅ Checks
- Work in groupe to create a **test suite**
- Cover both **standard cases** and **edge cases**
- Validate all mandatory requirements
- Matches the **project statement wording**
- Clear separation: compilation / interactive / non-interactive
- Uses **exact examples** from the subject
- Professional, readable, and checker-friendly

All code must pass the Betty style checker and be verified with Valgrind to ensure there are no memory leaks.

---

## ✨ Features
- Executes commands entered by the user
- Supports **interactive** and **non-interactive** modes
- Searches for executables using the `PATH` environment variable
- Uses system calls such as `fork`, `execve`, and `wait`
- Implements the following built-in commands:
    - `exit` – exits the shell
    - `env` – prints the current environment
- Handles errors such as command not found

---

## 📂 Project Structure

```
.
├── main.c
├── shell.c
├── parser.c
├── execute.c
├── builtins.c
├── utils.c
├── shell.h
├── man_1_simple_shell
├── AUTHORS
└── README.md
```
---
## 📘 Manual Page

A manual page for the shell is provided.
```bash
man ./man_1_simple_shell
```
----

## 🚫 Limitations
- No pipes (`|`)
- No redirections (`>`, `<`)
- No command chaining `;`, `&&`, `||`)
- No quote handling

---

## 🧪 Coding Style and Constraints
- Written in C
- Complies with the Betty coding style
- Compiled on Ubuntu 20.04
- Uses only allowed system calls and standard library functions
- No memory leaks (checked with valgrind)

---

## 📚 References
- Linux manual pages (`man fork`, `man execve`, `man wait`)
- GNU C Library documentation
- *Advanced Programming in the UNIX Environment* – W. Richard Stevens
- Holberton School

---

## 👨‍💻 Authors

Georgia Boulnois

Fabien Cousin
