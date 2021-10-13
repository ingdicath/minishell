# minishell

## Requirement

- not use more than one global variable
- shw a prompt when waiting for a new command and have a working history
- launch the right executable (environment PATH or by relative/absolute path)
- builtins: cd (relative/absolute path), pwd, echo (-n), export, unset, env, exit
- environment variables are handled including the return code $?
- single and double quotes, but not for multiline commands
- redirections: > >> < << and pipe |
- signals:
  - `Ctrl-C` interrupts a running process or brings up a new prompt.
  - `Ctrl-\` quits from a running program and does nothing on the prompt.
  - `Ctrl-D` throws an EOF or exits minishell.

[Writing your own shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

[How pipes work](http://www.rozmichelle.com/pipes-forks-dups/)

[Environment Variables](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap08.html)

[Process Completion Status](https://www.gnu.org/software/libc/manual/html_node/Process-Completion-Status.html)

[Exit Codes](https://tldp.org/LDP/abs/html/exitcodes.html#EXITCODESREF)

[termcap](https://man7.org/linux/man-pages/man5/termcap.5.html)


## install readline libraries

Open your terminal and run following commands:
```
ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" 2> /dev/null
```
```
brew install readline
```
