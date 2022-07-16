#include "minishell.h"

void	print_list(t_pipe *list)
{
	t_pipe *temp;
	temp = list;
	int i = 0;
	while (temp)
	{
		// printf("List%d:%s\n", i, temp->sub);
		printf("temp fd_in:%d\n",temp->fd_in);
		printf("temp fd_out:%d\n",temp->fd_out);
		printf("temp hd:%s\n",temp->hd);
		temp = temp->next;
		i++;
	}
}
