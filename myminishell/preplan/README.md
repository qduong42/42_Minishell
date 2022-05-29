**Allowedfunctions**

**READLINE:**

readline -> called once 1)
rl_on_new_line
rl_replace_line
rl_redisplay
add_history 2) add history -> easy
rl_clear_history -> not used

printf
malloc
free
write
open
read
close
fork
wait
waitpid
signal
sigaction
kill
exit
access

getcwd
	-get the pathname of the current work directory
	char *getcwd(char *buf, size_t size);
chdir
	-The chdir() changes the cwd to path, which can be relative to the cwd or an absolute path name.
	-Return Value: upon success: 0 -- else: -1
execve
dup
dup2
pipe


wait3 -> not used
wait4 -> not used
sigemptyset -> not used
sigaddset -> not used

stat -> not used
fstat -> not used
lstat -> not used
unlink -> not used

opendir -> not used
readdir -> not used
closedir -> not used

strerror -> not used
perror -> not used
isatty -> not used
ttyname -> not used
ttyslot -> not used
ioctl -> not used

getenv -> not used
tcsetattr -> not used
tcgetattr -> not used
tgetent -> not used
tgetflag -> not used

tgetnum -> not used
tgetstr -> not used
tgoto -> not used
tputs -> not used

**INVESTIGATIONS**

1) customize prompt color https://www.tecmint.com/customize-bash-colors-terminal-prompt-linux/
	foreground color vs background color

2) ENV -> see burning questions.

3) 

**BURNING QUESTIONS**

1) what is env used for and why is it saved? -> variables environments, to get $(HOME) $(PATH) for command execution
	-https://www.shell-tips.com/bash/environment-variables/#gsc.tab=0

**TO-DO**



**NOT_HANDLED**

ls -la | sort >&mout -> &mout handled just as filename, while bash behavior "ignores" &
cd -  --> should go to "previous" directory that you were in. probably - expands to old PWD.