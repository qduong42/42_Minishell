#include "minishell.h"

void	print_list(t_pipe *list)
{
	t_pipe *temp;
	temp = list;
	int i = 0;
	while (temp)
	{
		// printf("List%d:%s\n", i, temp->sub);
		printf("temp fd_in:i:%d:%d\n",i, temp->fd_in);
		printf("temp fd_out:%d:%d\n",i ,temp->fd_out);
		printf("temp hd:%d:%s\n",i, temp->hd);
		i++;
		printf("\n");
		temp = temp->next;
	}
}
