#include "minishell.h"

void	print_list(t_pipe *list)
{
	t_pipe *temp;
	temp = list;
	int i = 0;
	while (temp)
	{
		printf("List%d:%s\n", i, temp->sub);
		temp = temp->next;
		i++;
	}
}
