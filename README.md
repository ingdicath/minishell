![](https://github.com/ingdicath/images_md/blob/main/minishell.png)

# **minishell**
CODAM project Curriculum, subject updated on May 2021. 

- **Project type**: Unix logic.
- **Objective**: Create a simple shell, understanding concepts about processes and file descriptors.

This is a group project developed by [H. Lin] (https://github.com/Hz-Lin) & [D. Salamanca] (https://github.com/ingdicath)

----
## Requirements

This project is aimed create a shell that mimics bash, following the below requirements:

- Not interpret unclosed quotes or unspecified special characters like `\` or `;`.
- Show a prompt when waiting for a new command.
- Have a working History.
- Search and launch the right _executable_ (based on the PATH variable or by using
  relative or absolute path)
- It must implement the builtins:
  - `echo` with option -n
  - `cd` with only a relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options
  - single `'` and double `"` quotes, not for multiline commands.
- Redirections:
  - `<` should redirect input.
  - `>` should redirect output.
  - `<<` read input from the current source until a line containing only the delimiter is seen.
  - `>>` should redirect output with append mode.
- Pipes `|` 
- Environment variables ($ followed by characters) should expand to their values.
- `$?` should expand to the exit status of the most recently executed foreground
      pipeline.
- Signals `ctrl-C` `ctrl-D` `ctrl-\` should work like in bash.
- When interactive:
  - ctrl-C print a new prompt on a newline.
  - ctrl-D exit the shell.
  - ctrl-\ do nothing.

----
## Prerequisites

Be sure you have `readline` library installed in your computer.


---
## How to build :hammer:

1. Clone the repository `git clone git@github.com:ingdicath/minishell.git`
2. Go into folder ```cd minishell```
3. Type in the terminal ```make```
4. Execute `./minishell`

