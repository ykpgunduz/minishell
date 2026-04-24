*This project has been created as part of the 42 curriculum by yagunduz, zkarali.*

# Minishell

## Description
Minishell is a project in the 42 curriculum that aims to recreate a simple UNIX command shell, mirroring the core functionalities of Bash. The goal of this project is to introduce students to the concepts of process creation, file descriptors, signals, and abstract syntax trees (or at least complex parsing logic) in C. 

The project is divided into two primary modules:
- **Parser**: Responsible for reading the user input, tokenizing it, handling quotes (single and double), expanding environment variables (`$VAR`, `$?`), and preparing a structured command format.
- **Executor**: Responsible for taking the parsed commands and executing them. It handles pipes (`|`), input/output redirections (`<`, `>`, `<<`, `>>`), and executing both system binaries (via `execve`) and built-in commands.

This version features a modular architecture, keeping the parsing phase and execution phase cleanly separated, fully conforming to the strict 42 Norminette coding standard.

## Instructions

### Compilation
The project includes a unified `Makefile` at the root directory that compiles all submodules (parser, executor, builtins, libft). To compile the project, simply run:

```bash
make
```

If you need to clean up the generated object files or completely recompile the project, you can use:
- `make clean`: Removes all `.o` object files.
- `make fclean`: Removes the object files and the final `minishell` executable.
- `make re`: Performs `fclean` followed by `make` to completely rebuild the project.

### Installation
Ensure that you have the GNU `readline` library installed on your system, as it is heavily utilized for the prompt interface and command history.

On macOS (using Homebrew):
```bash
brew install readline
```
*(Note: The Makefile dynamically checks the path using `brew --prefix readline`)*

On Linux (Ubuntu/Debian):
```bash
sudo apt-get install libreadline-dev
```

### Execution
Once compiled, you can launch the shell by running:
```bash
./minishell
```

You can then start typing standard UNIX commands exactly as you would in Bash!

## Resources
- **Bash Reference Manual**: The ultimate guide for understanding how quoting, parsing, and execution are supposed to behave.
- **GNU Readline Library**: Documentation for history management and custom prompt interfaces.
- **System Calls**: `man 2 fork`, `man 2 execve`, `man 2 pipe`, `man 2 dup2`, and `man 3 signal`.

**AI Usage Statement:**
AI was used during the later stages of this project primarily as a pair-programming assistant to resolve `Norminette` formatting issues and architectural refactoring. Specifically, AI helped to:
- Reduce excessive function arguments by centralizing state variables into unified structures (`t_ms *data`), directly addressing `TOO_MANY_ARGS` errors in the parser module.
- Fix indentation and character limits in `quote.c` and `expander.c`.
- Refactor the `Makefile` architecture by removing redundant sub-makefiles and merging all build rules (including `libft`) into a single, highly optimized root `Makefile`.
- Generate and format this README documentation according to 42 subject guidelines.
