#include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
    while(envp[i])
        printf("%s\n",envp[i++]);
}
