#include "minishell.h"

void	print_list(t_pipe *list, int a)
{
	t_pipe *temp;
	temp = list;
	int i = 0;
	while (temp)
	{
		if (a == 1)
		{
			printf("subpipe%d\t%s", i,temp->sub);
		}
		// printf("List%d:%s\n", i, temp->sub);
		if (a == 2)
		{
		printf("temp fd_in:i:%d\t%d\n",i, temp->fd_in);
		printf("temp fd_out:%d\t%d\n",i ,temp->fd_out);
		printf("temp hd:%d\t%s\n",i, temp->hd);
		}
		i++;
		printf("\n");
		temp = temp->next;
	}
}
