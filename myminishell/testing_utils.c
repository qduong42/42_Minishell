#include "minishell.h"

void	print_list(t_list *list)
{
	t_list *temp;
	temp = list;
	int i = 0;
	while (temp)
	{
		printf("List%d:%s\n", i, temp->content);
		temp = temp->next;
		i++;
	}
}
