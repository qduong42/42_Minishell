# include "../pipex.h"

int	ft_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->content);
		env = env->next;
	}
	return (0);
}
