#include "minishell.h"

void	input_handle(char *string, t_pipe *s)
{
	printf("STRING%s\tYIPPE:%s\n", string, s->sub);
}